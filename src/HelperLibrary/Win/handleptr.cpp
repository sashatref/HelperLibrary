#include "handleptr.h"

#include <IcmpAPI.h>


void HelperLibraryNS::HandleDeleter::operator()(HANDLE _handle)
{
    if(_handle)
    {
        ::CloseHandle(_handle);
    }
}

void HelperLibraryNS::IcmpHandleDeleter::operator ()(HANDLE _handle)
{
    if(_handle)
    {
        ::IcmpCloseHandle(_handle);
    }
}
