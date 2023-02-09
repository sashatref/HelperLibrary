#pragma once

#include <QString>
#include "../export.h"

class HELPERLIBRARY_EXPORT ProcessInfo
{
public:
    qint64 maxUsedRam = 0;
    qint64 currentUsedRam = 0;

    qint64 maxUsedPageFile = 0;
    qint64 currentUsedPageFile = 0;


    //существует ли процесс
    static bool exist(const QString &_processName);

    //получить список процессов
    static QStringList getProcessList();

    //"убить" процесс
    static void kill(const QString &_processName);

    static DWORD currentPID();

    static ProcessInfo forProcess( DWORD processID );

    static ProcessInfo current();

    static QList<DWORD> getThreadList();
};

