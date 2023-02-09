#ifndef LOGGERHELPER_H
#define LOGGERHELPER_H

#include "../export.h"

namespace LoggerQt
{

class HELPERLIBRARY_EXPORT LoggerHelper
{
public:
    static void logMessage(const QString &_text, QtMsgType _type);
};

}

#endif // LOGGERHELPER_H
