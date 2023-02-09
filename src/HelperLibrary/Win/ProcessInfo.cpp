#include "ProcessInfo.h"
#include "handleptr.h"
#include "../Exceptions/userexception.h"

bool ProcessInfo::exist(const QString &_processName)
{
    return getProcessList().contains(_processName);
}

QStringList ProcessInfo::getProcessList()
{
    QStringList processList;

    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (hSnap == NULL)
    {
        return processList;
    }

    PROCESSENTRY32 proc;
    proc.dwSize = sizeof(PROCESSENTRY32);

    if (Process32First(hSnap, &proc))
    {
        processList << QString::fromStdWString(proc.szExeFile);

        while (Process32Next(hSnap, &proc))
        {
            processList << QString::fromStdWString(proc.szExeFile);
        }
    }

    return processList;
}

void ProcessInfo::kill(const QString &_processName)
{
    QProcess::startDetached("taskkill", QStringList() << "/F" << "/IM" << _processName);
}


DWORD ProcessInfo::currentPID()
{
    return GetCurrentProcessId();
}

ProcessInfo ProcessInfo::forProcess(DWORD processID)
{
    ProcessInfo out;

    PROCESS_MEMORY_COUNTERS pmc;

    HelperLibraryNS::HandlePtr hProcess( OpenProcess(  PROCESS_QUERY_INFORMATION |
                                               PROCESS_VM_READ,
                                               FALSE, processID ) );
    if (hProcess == NULL)
    {
        throwException("Error while open process [%1]", processID);
    }

    if ( GetProcessMemoryInfo( hProcess.get(), &pmc, sizeof(pmc)) )
    {
        out.currentUsedRam = pmc.WorkingSetSize;
        out.maxUsedRam = pmc.PeakWorkingSetSize;
        out.maxUsedPageFile = pmc.PeakPagefileUsage;
        out.currentUsedPageFile = pmc.PagefileUsage;
    }

    return out;
}

ProcessInfo ProcessInfo::current()
{
    return forProcess(currentPID());
}

QList<DWORD> ProcessInfo::getThreadList()
{
    QList<DWORD> out;

    DWORD processId = currentPID();

    HelperLibraryNS::HandlePtr h(CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0));
    if (h.get() != INVALID_HANDLE_VALUE)
    {
        THREADENTRY32 te;
        te.dwSize = sizeof(te);
        if (Thread32First(h.get(), &te))
        {
            do
            {
                if (te.dwSize >= FIELD_OFFSET(THREADENTRY32, th32OwnerProcessID) +
                        sizeof(te.th32OwnerProcessID))
                {
                    if(te.th32OwnerProcessID == processId)
                    {
                        out << te.th32ThreadID;
                    }
                }
                te.dwSize = sizeof(te);
            } while (Thread32Next(h.get(), &te));
        }
    }

    return out;
}
