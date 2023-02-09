#include "customstackwalker.h"



CustomStackWalker::CustomStackWalker()
{

}

QString CustomStackWalker::getTraceText() const
{
    return m_result.join("\n");
}

QStringList CustomStackWalker::getTraceList() const
{
    return m_result;
}

void CustomStackWalker::OnCallstackEntry(StackWalker::CallstackEntryType eType,
                                         StackWalker::CallstackEntry &entry)
{
    switch(eType)
    {
    case firstEntry:
        break;
    case nextEntry:
        break;
    case lastEntry:
        break;
    }

    m_result.append(QString("%3! %1() Line %2")
            .arg(entry.name)
            .arg(entry.lineNumber)
            .arg(entry.moduleName));
}

void CustomStackWalker::OnOutput(LPCSTR)
{

}

