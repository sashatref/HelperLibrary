#include "basepluginmanager.h"
#include "../Widgets/layoutsaver.h"
#include "../Serialization/serializer.h"
#include "../converterfunctions.h"
#include "../helperscontainter.h"

#include <QPluginLoader>
#include <QLibraryInfo>

namespace HelperLibraryNS
{

BasePluginManager::BasePluginManager(QObject *_parent):
    QObject(_parent)
{

}

BasePluginManager::~BasePluginManager()
{
    pluginDelete();
}


void BasePluginManager::loadPlugins(const QDir &_pluginsDir, const PluginEnableMap &_enableList)
{
    QStringList filter = QStringList()
#ifdef Q_OS_WIN
            << QString("*.dll");
#else
            << QString("*.so");
#endif

    QStringList files = _pluginsDir.entryList(filter, QDir::Files);

    const bool appDebug = QLibraryInfo::isDebugBuild();

    for(const QString &fileName : files)
    {
        QPluginLoader *loader = new QPluginLoader(_pluginsDir.absoluteFilePath(fileName), this);

        const QVariantMap metaData = loader->metaData().toVariantMap();
        const QString uniqueName = metaData["IID"].toString();
//        const QVariantMap pluginMetaData = metaData["MetaData"].toMap();

        bool pluginDebug = metaData.value("debug").toBool();
        if(pluginDebug != appDebug)
        {
            continue;
        }

        if (!loader->isLoaded())
        {
            if (!loader->load())
            {
                emit logMessage(tr("Ошибка загрузки плагина: %1. %2")
                                .arg(fileName)
                                .arg(loader->errorString()),
                                QtCriticalMsg);
                continue;
            }
        }

        QObject * obj = loader->instance();
        if (AbstractPlugin * plugin = qobject_cast<AbstractPlugin *>(obj))
        {
            plugin->m_uniqueName = uniqueName;
            if(castPlugin(plugin))
            {
                m_pluginList.append(plugin);
                if(_enableList.contains(plugin->getUniquePluginName()) &&
                        !_enableList[plugin->getUniquePluginName()])
                {
                    plugin->m_isLoaded = false;
                } else
                {
                    plugin->m_isLoaded = true;

                    emit logMessage(tr("Плагин загружен: %1 (%2)")
                                    .arg(fileName)
                                    .arg(plugin->getVersion()), QtWarningMsg);

                    connectPlugin(plugin);
                }
            } else
            {
                delete plugin;
                loader->unload();
            }
        }
    }



    {   //загрузка статически прилинкованных плагинов
        QObjectList instances = QPluginLoader::staticInstances();
        QVector<QStaticPlugin> metaDataVec = QPluginLoader::staticPlugins();

        const int count = qMin(instances.size(), metaDataVec.size());

        for(int i = 0 ; i < count; i++)
        {
            if (AbstractPlugin * plugin = qobject_cast<AbstractPlugin *>(instances.at(i)))
            {
                plugin->m_uniqueName = metaDataVec.at(i).metaData().toVariantMap()["IID"].toString();
                if(castPlugin(plugin))
                {
                    m_pluginList.append(plugin);
                    if(_enableList.contains(plugin->getUniquePluginName()) &&
                            !_enableList[plugin->getUniquePluginName()])
                    {
                        plugin->m_isLoaded = false;
                    } else
                    {
                        plugin->m_isLoaded = true;

                        emit logMessage(tr("Плагин загружен: %1 (%2)")
                                        .arg(plugin->getName())
                                        .arg(plugin->getVersion()), QtWarningMsg);

                        connectPlugin(plugin);
                    }
                }
            }
        }
    }


    for(auto *plugin : m_pluginList)
    {
        if(_enableList.contains(plugin->getUniquePluginName()))
        {
            plugin->m_isEnabled = _enableList[plugin->getUniquePluginName()];
        }
    }

    postLoadPlugins();
}


QList<AbstractPlugin *> BasePluginManager::getAbstractPluginList() const
{
    return m_pluginList;
}

QList<AbstractPlugin *> BasePluginManager::getLoadedPlugins() const
{
    return ContainerHelper::Select<AbstractPlugin*>(m_pluginList, [](AbstractPlugin *_pl)
    {
        return _pl->m_isLoaded;
    });
}



void BasePluginManager::pluginDelete()
{
    qDeleteAll(m_pluginList);
    m_pluginList.clear();

    postPluginDelete();
}

void BasePluginManager::loadPluginSettings(const QString &_settingPath)
{
    for(auto *plugin : getAbstractPluginList())
    {
        QVariant pluginSettings;

        try
        {
            SerializerQt::Serializer::load(pluginSettings,
                             QDir(_settingPath),
                             plugin->getUniquePluginName(), SerializerQt::Serializer::ExceptOnError);
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

void BasePluginManager::savePluginSettings(const QString &_settingPath) const
{
    for(auto *plugin : getAbstractPluginList())
    {
        QVariant pluginSettings = plugin->onSettingsSave();

        try
        {
            SerializerQt::Serializer::append(pluginSettings,
                               QDir(_settingPath),
                               plugin->getUniquePluginName(), SerializerQt::Serializer::ExceptOnError);
        } catch(std::exception &e)
        {
            qDebug() << e.what();
        }
    }
}

void BasePluginManager::loadPluginLayoutState(const QString &_layoutPath)
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

void BasePluginManager::savePluginLayoutState(const QString &_layoutPath) const
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

}
