#pragma once

#include <QObject>
#include <QVariant>
#include <QDir>

#include "../export.h"
#include "abstractplugin.h"
#include "pluginliststate.h"
#include "preloadplugininfo.h"

namespace HelperLibraryNS
{

class HELPERLIBRARY_EXPORT BasePluginCreatorManager : public QObject
{
    Q_OBJECT
public:
    BasePluginCreatorManager(QObject *_parent = nullptr);

    ~BasePluginCreatorManager();

    void loadPlugins(const QDir &_pluginsDir, const QString &_iid);

    void loadPlugins(const QStringList &_files, const QString &_iid);


    QList<AbstractPlugin*> getAbstractPluginList() const;
    QList<AbstractPlugin*> getLoadedPlugins() const;

    template<class Type>
    QList<Type*> getLoadedPlugins() const
    {
        QList<Type*> out;

        for(auto *pl : getLoadedPlugins())
        {
            Type * casted = qobject_cast<Type*>(pl);
            if(casted)
            {
                out << casted;
            }
        }

        return out;
    }

    void pluginDelete();

    void loadPluginSettings(const QString &_settingPath);
    void savePluginSettings(const QString &_settingPath) const;

    void loadPluginLayoutState(const QString &_layoutPath);
    void savePluginLayoutState(const QString &_layoutPath) const;

    void createPluginInstanses(const PluginEnableMap &_plConfig);

    AbstractPlugin *createPlugin(const QString &_pluginName);

protected:
    virtual bool castPlugin(AbstractPlugin *_plugin) = 0;
    virtual void connectPlugin(AbstractPlugin *_plugin) = 0;
    virtual void postPluginDelete() {}
    virtual void postLoadPlugins() {}

signals:
    void logMessage(const QString &_text, QtMsgType _type);

private:
    void addPluginInfo(QObject *_creator,
                       const QVariantMap &_metaData,
                       const QString &_filePath,
                       const QString &_iid, bool _isStatic);

    QMap<QString, PreloadPluginInfo> m_preloadData;
    QMap<QString, QSharedPointer<AbstractPlugin>> m_pluginMap;

    QList<AbstractPlugin*> m_plugins;
};

}
