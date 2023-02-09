#pragma once

#include <Windows.h>
#include <memory>
#include "../export.h"

namespace HelperLibraryNS
{

struct HELPERLIBRARY_EXPORT HandleDeleter
{
    void operator()(HANDLE _handle);
};

using HandlePtr = std::unique_ptr<void, HandleDeleter>;

struct HELPERLIBRARY_EXPORT IcmpHandleDeleter
{
    void operator ()(HANDLE _handle);
};

using IcmpPtr = std::unique_ptr<void, IcmpHandleDeleter>;
}

