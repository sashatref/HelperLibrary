#pragma once

#include "handleptr.h"
#include "../export.h"

namespace HelperLibraryNS
{

class HELPERLIBRARY_EXPORT IcmpProvider
{
public:
    IcmpProvider();
    ~IcmpProvider();

    bool ping(const QString &_addr, int timeout = 1000);

    static bool pingAddr(const QString &_addr, int timeout = 1000);

private:
    IcmpPtr m_ptr;
};

}
