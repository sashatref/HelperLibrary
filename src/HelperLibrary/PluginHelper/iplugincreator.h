#pragma once

#include <QMap>

#include "../export.h"
#include "abstractplugin.h"

namespace HelperLibraryNS
{

class HELPERLIBRARY_EXPORT IPluginCreator
{
public:
    virtual ~IPluginCreator() = default;
    virtual AbstractPlugin *createPlugin(const QString &_name) = 0;

    virtual QStringList keys() = 0;
};

class HELPERLIBRARY_EXPORT IMultiPluginCreator : public IPluginCreator
{
public:
    virtual AbstractPlugin *createPlugin(const QString &_name) override;

protected:
    template<class PluginType>
    void registerPlugin(const QString &_name)
    {
        registerPlugin(_name, []{return new PluginType();});
    }

    void registerPlugin(const QString &_name, std::function<AbstractPlugin*()> _creatorFunc);
    virtual QStringList keys() override;

private:
    QMap<QString, std::function<AbstractPlugin*()>> m_factory;
};

}

Q_DECLARE_INTERFACE(HelperLibraryNS::IPluginCreator, "avia.HelperLibraryNS.IPluginCreator")




