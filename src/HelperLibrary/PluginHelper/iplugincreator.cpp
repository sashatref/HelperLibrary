#include "iplugincreator.h"

namespace HelperLibraryNS
{
    AbstractPlugin *IMultiPluginCreator::createPlugin(const QString &_name)
    {
        auto it = m_factory.find(_name);
        if(it == m_factory.end())
        {
            return nullptr;
        }

        return it.value()();
    }

    void IMultiPluginCreator::registerPlugin(const QString &_name, std::function<AbstractPlugin *()> _creatorFunc)
    {
        m_factory[_name] = _creatorFunc;
    }

    QStringList IMultiPluginCreator::keys()
    {
        return m_factory.keys();
    }
}


