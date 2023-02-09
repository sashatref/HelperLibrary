#pragma once
#include <QtCore/qglobal.h>

#ifdef HelperLibrary_BUILD_STATIC
    #define HELPERLIBRARY_EXPORT
#else
    #if defined(HELPERLIBRARY)
        #define HELPERLIBRARY_EXPORT Q_DECL_EXPORT
    #else
        #define HELPERLIBRARY_EXPORT Q_DECL_IMPORT
    #endif
#endif
