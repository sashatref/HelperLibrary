#pragma once

#include "export.h"

#include <QStringList>

namespace HelperLibraryNS
{

class HELPERLIBRARY_EXPORT CmdArgs
{
public:
    CmdArgs(const QStringList &_cmdArgs = QStringList());
    ~CmdArgs();

    //не нужно изменять это значение, это только чтоб передавать в Си функции
    int &getArgc() {return m_argc;}
    char **getArgv() {return m_argv;}

    void setArguments(const QStringList &_cmdArgs);

private:
    void destroyArgs();

    Q_DISABLE_COPY(CmdArgs)

    int m_argc = 0;
    char **m_argv = nullptr;
};

}

