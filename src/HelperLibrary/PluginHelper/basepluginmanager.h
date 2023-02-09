#pragma once

#include <QObject>
#include <QVariant>
#include <QDir>

#include "../export.h"
#include "abstractplugin.h"
#include "pluginliststate.h"

namespace HelperLibraryNS
{

class HELPERLIBRARY_EXPORT BasePluginManager : public QObject
{
    Q_OBJECT
public:
    BasePluginManager(QObject *_parent = nullptr);
    ~BasePluginManager();

    void loadPlugins(const QDir &_pluginsDir, const PluginEnableMap &_enableList);

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

protected:
    virtual bool castPlugin(AbstractPlugin *_plugin) = 0;
    virtual void connectPlugin(AbstractPlugin *_plugin) = 0;
    virtual void postPluginDelete() {}
    virtual void postLoadPlugins() {}

signals:
    void logMessage(const QString &_text, QtMsgType _type);

private:
    QList<AbstractPlugin*> m_pluginList;
};

}
