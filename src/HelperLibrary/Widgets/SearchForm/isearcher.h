#pragma once

namespace HelperLibraryNS
{

class ISearcher
{
public:
    virtual ~ISearcher() = default;

    virtual bool checkText(const QString &_text) = 0;
};

}

