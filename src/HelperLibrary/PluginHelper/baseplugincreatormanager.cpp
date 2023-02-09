#include "baseplugincreatormanager.h"
#include "../Widgets/layoutsaver.h"
#include "../Serialization/serializer.h"
#include "../converterfunctions.h"
#include "../helperscontainter.h"
#include "../functions.h"

#include <QPluginLoader>
#include <QLibraryInfo>

namespace HelperLibraryNS
{

BasePluginCreatorManager::BasePluginCreatorManager(QObject *_parent):
    QObject(_parent)
{

}

BasePluginCreatorManager::~BasePluginCreatorManager()
{


}

void BasePluginCreatorManager::loadPlugins(const QDir &_pluginsDir, const QString &_iid)
{
    QStringList filter = QStringList()
#ifdef Q_OS_WIN
            << QString("*.dll");
#else
            << QString("*.so");
#endif

    QFileInfoList fInfoArr = _pluginsDir.entryInfoList(filter, QDir::Files);

    QStringList files;

    for(auto &it : fInfoArr)
    {
        files << it.absoluteFilePath();
    }

    loadPlugins(files, _iid);
}

void BasePluginCreatorManager::loadPlugins(const QStringList &_files, const QString &_iid)
{
    {   //загрузка статически прилинкованных плагинов
        QObjectList instances = QPluginLoader::staticInstances();
        QVector<QStaticPlugin> metaDataVec = QPluginLoader::staticPlugins();

        const int count = qMin(instances.size(), metaDataVec.size());

        for(int i = 0 ; i < count; i++)
        {
            addPluginInfo(instances.at(i),
                          metaDataVec.at(i).metaData().toVariantMap(),
                          "", _iid, true);
        }
    }

    for(const QString &fileName : _files)
    {
        QPluginLoader *loader = new QPluginLoader(fileName, this);
        QObject *instance = loader->instance();
        if(instance == nullptr)
        {
            emit logMessage(tr("Ошибка загрузки плагина: %1. %2")
                            .arg(fileName)
                            .arg(loader->errorString()),
                            QtCriticalMsg);
            continue;
        }

        const QVariantMap metaData = loader->metaData().toVariantMap();
        addPluginInfo(instance, metaData, fileName, _iid, false);
    }
}

void BasePluginCreatorManager::addPluginInfo(QObject *_creator,
                                             const QVariantMap &_metaData,
                                             const QString &_filePath,
                                             const QString &_iid,
                                             bool _isStatic)
{
    const bool appDebug = QLibraryInfo::isDebugBuild();

    bool pluginDebug = _metaData.value("debug").toBool();
    if(pluginDebug != appDebug)
    {
        return;
    }

    const QString iid = _metaData["IID"].toString();
    if(iid != _iid)
    {
        return;
    }

    const QString className = _metaData["className"].toString();
    IPluginCreator * pluginCreator = qobject_cast<IPluginCreator *>(_creator);
    if(pluginCreator == nullptr)
    {
        emit logMessage(tr("%1 | Ошибка приведения класса [%2] к интерфейсу [IPluginCreator]")
                        .arg(__FUNCTION__, className), QtCriticalMsg);
        return;
    }

    const QVariantMap pluginMetaData = _metaData["MetaData"].toMap();
    const QStringList keys = pluginCreator->keys();

    for(const QString &name : keys)
    {
        if(m_preloadData.contains(name))
        {
            emit logMessage(Text::format("%2 | PluginFactory with name [%1] already exist, something wrong!",
                                         name, __FUNCTION__),
                            QtFatalMsg);
            continue;
        }

        PreloadPluginInfo plInfo;
        plInfo.fileName = QFileInfo(_filePath).fileName();
        plInfo.pluginName = name;
        plInfo.creator = pluginCreator;
        plInfo.loaded = plInfo.creator;
        plInfo.className = className;
        plInfo.isStatic = _isStatic;
        m_preloadData[name] = plInfo;

        if(plInfo.creator == nullptr)
        {
            emit logMessage(tr("Плагин [%1] | Ошибка создания интерфейса [IPluginCreator*]")
                            .arg(plInfo.fileName), QtCriticalMsg);
        }
    }
}

QList<AbstractPlugin *> BasePluginCreatorManager::getAbstractPluginList() const
{
    return m_plugins;
}

QList<AbstractPlugin *> BasePluginCreatorManager::getLoadedPlugins() const
{
    return ContainerHelper::Select<AbstractPlugin*>(m_plugins, [](AbstractPlugin *_pl)
    {
        return _pl->m_isLoaded;
    });
}

void BasePluginCreatorManager::pluginDelete()
{
    for(auto it : getLoadedPlugins())
    {
        it->turnOff();
    }

    m_pluginMap.clear();
    m_plugins.clear();

    postPluginDelete();
}

void BasePluginCreatorManager::loadPluginSettings(const QString &_settingPath)
{
    using SerializerQt::Serializer;

    for(auto *plugin : getAbstractPluginList())
    {
        QVariant pluginSettings;

        try
        {
            Serializer::load(pluginSettings,
                             QDir(_settingPath),
                             plugin->getUniquePluginName(), Serializer::ExceptOnError);
        } catch(std::exception &e)
        {
            emit logMessage(QString("PluginManager::loadPluginSettings | "
                                    "Error while parse plugin config file [%1]")
                            .arg(e.what()),
                            QtCriticalMsg);
        }

        plugin->onSettingsLoad(pluginSettings);
    }
}

void BasePluginCreatorManager::savePluginSettings(const QString &_settingPath) const
{
    using SerializerQt::Serializer;

    for(auto *plugin : getAbstractPluginList())
    {
        QVariant pluginSettings = plugin->onSettingsSave();

        try
        {
            Serializer::append(pluginSettings,
                               QDir(_settingPath),
                               plugin->getUniquePluginName(), Serializer::ExceptOnError);
        } catch(std::exception &e)
        {
            qDebug() << e.what();
        }
    }
}

void BasePluginCreatorManager::loadPluginLayoutState(const QString &_layoutPath)
{
    for(auto *pl : getLoadedPlugins())
    {
        LayoutSaver saver;
        saver.loadFromFile(QString("%1/%2.bin")
                           .arg(_layoutPath)
                           .arg(pl->getUniquePluginName()));

        pl->loadLayout(saver);
    }
}

void BasePluginCreatorManager::savePluginLayoutState(const QString &_layoutPath) const
{
    QDir ltDir(_layoutPath);
    if(!ltDir.exists())
    {
        QDir().mkdir(_layoutPath);
    }

    for(auto *pl : getLoadedPlugins())
    {
        LayoutSaver saver;
        pl->saveLayout(saver);
        saver.saveToFile(QString("%1/%2.bin")
                         .arg(_layoutPath)
                         .arg(pl->getUniquePluginName()));
    }
}

void BasePluginCreatorManager::createPluginInstanses(const PluginEnableMap &_plConfig)
{
    for(auto it = m_preloadData.begin(); it != m_preloadData.end(); ++it)
    {
        PreloadPluginInfo plInfo = it.value();

        QSharedPointer<HelperLibraryNS::AbstractPlugin> absPlugin(plInfo.creator->createPlugin(plInfo.pluginName));
        if(absPlugin == nullptr)
        {
            emit logMessage(tr("%1 | Ошибка создания плагина [%2]")
                            .arg(__FUNCTION__)
                            .arg(plInfo.pluginName), QtCriticalMsg);
            continue;
        }

        if(!castPlugin(absPlugin.data()))
        {
            emit logMessage(tr("%1 | Ошибка приведения интефейса для плагина [%2]")
                            .arg(__FUNCTION__)
                            .arg(plInfo.pluginName), QtCriticalMsg);
            continue;
        }

        emit logMessage(tr("Плагин загружен [%1]").arg(it.key()), QtInfoMsg);

        absPlugin->m_uniqueName = it.key();
        absPlugin->m_isEnabled = _plConfig.value(it.key(), true);

        if(absPlugin->m_isEnabled)
        {
            absPlugin->m_isLoaded = true;
            absPlugin->turnOn();
            connectPlugin(absPlugin.data());
        }

        m_pluginMap[it.key()] = absPlugin;
        m_plugins << absPlugin.data();
    }
}

AbstractPlugin *BasePluginCreatorManager::createPlugin(const QString &_pluginName)
{
    auto it = m_preloadData.find(_pluginName);
    if(it == m_preloadData.end())
    {
        return nullptr;
    }

    return it.value().creator->createPlugin(_pluginName);
}

}
