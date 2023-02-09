#include "leakchecker.h"

namespace HelperLibraryNS
{

bool LeakChecker::isEnabled = true;
QSet<LeakChecker*> LeakChecker::leakCheckerList;

LeakChecker::LeakChecker(const QString &_className):
    m_className(_className)
{
    leakCheckerList << this;
}

LeakChecker::~LeakChecker()
{
    leakCheckerList.remove(this);

    check();
}

void LeakChecker::inc()
{
    m_count++;

    if(isEnabled)
    {
        qDebug() << QString("LeakChecker |  %1() | Count [%2]").arg(m_className).arg(m_count);
    }
}

void LeakChecker::dec()
{
    m_count--;

    if(isEnabled)
    {
        qDebug() << QString("LeakChecker | ~%1() | Count [%2]").arg(m_className).arg(m_count);
    }
}

void LeakChecker::check()
{
    if(isEnabled)
    {
        if(m_count != 0)
        {
            qDebug() << QString("LeakChecker | %1 | Leak detected | Count [%2]")
                          .arg(m_className)
                          .arg(m_count);
        }
    }
}

void LeakChecker::checkAll()
{
    qDebug() << "LeakChecker::checkAll():" << leakCheckerList.size();

    if(isEnabled)
    {
        for(auto it = leakCheckerList.begin(); it != leakCheckerList.end(); ++it)
        {
            (*it)->check();
        }
    }
}

}
