#include "cmdargs.h"

namespace HelperLibraryNS
{
CmdArgs::CmdArgs(const QStringList &_cmdArgs)
{
    setArguments(_cmdArgs);
}

CmdArgs::~CmdArgs()
{
    destroyArgs();
}

void CmdArgs::setArguments(const QStringList &_cmdArgs)
{
    destroyArgs();

    m_argc = _cmdArgs.size();

    m_argv = new char*[m_argc];

    for(int i = 0 ; i < _cmdArgs.size(); i++)
    {
        QString item = _cmdArgs.at(i);

        m_argv[i] = new char[item.size() + 1];
        strcpy(m_argv[i], item.toUtf8().constData());
    }
}

void CmdArgs::destroyArgs()
{
    for(int i = 0 ; i < m_argc; i++)
    {
        delete[] m_argv[i];
    }

    delete[] m_argv;

    m_argc = 0;
    m_argv = nullptr;
}

}


