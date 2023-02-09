#pragma once

#include "export.h"

namespace HelperLibraryNS
{

class HELPERLIBRARY_EXPORT LeakChecker
{
public:
    LeakChecker(const QString &_className);
    ~LeakChecker();

    void inc();
    void dec();

    void check();

    static QSet<LeakChecker*> leakCheckerList;

    static void checkAll();

private:
    static bool isEnabled;

    QString m_className;
    int m_count = 0;
};

}

