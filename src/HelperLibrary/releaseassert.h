#pragma once

#include "Exceptions/userexception.h"

#ifdef _DEBUG
    #define R_ASSERT_X(expression, text) Q_ASSERT_X(expression, Q_FUNC_INFO, qPrintable(text));
    #define R_ASSERT(expression) Q_ASSERT(expression);
#else
    #define R_ASSERT_X(expression, text)							\
    if (!(expression))												\
    {																\
        throw HelperLibrary::UserExceptions::BaseException(text);                  \
    }

    #define R_ASSERT(expression)									\
    if (!(expression))												\
    {																\
        throw HelperLibrary::UserExceptions::BaseException(#expression"==0");      \
    }
#endif

