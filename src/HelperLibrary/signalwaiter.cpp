#include "signalwaiter.h"

#include <QDeadlineTimer>

SignalWaiter::~SignalWaiter()
{
    m_timer.stop();
    m_loop.quit();
}

bool SignalWaiter::wait(int _msec)
{
    m_timer.start(_msec);
    m_loop.exec();
    return m_timedOut;
}

SignalWaiter::ExitStatus SignalWaiter::wait(int _msecTotal, std::function<bool ()> _checkExpr, int _exprCheckInterval)
{
    int iterCount = _msecTotal / _exprCheckInterval;

    for(int i = 0 ; i < iterCount ;i++)
    {
        if(_checkExpr())
        {
            return esExprReturnTrue;
        }

        if(!wait(_exprCheckInterval))
        {
            return esSuccess;
        }
    }
    return esTimedOut;
}

bool SignalWaiter::waitExp(int _msecTotal, int _exprCheckInterval, std::function<bool ()> _checkExpr)
{
    QDeadlineTimer deadline(_msecTotal);
    do
    {
        if(_checkExpr())
        {
            return true;
        }

        QTimer timer;
        QEventLoop loop;
        QObject::connect(&timer, &QTimer::timeout, &loop, &QEventLoop::quit);
        timer.start(_exprCheckInterval);
        loop.exec();
    } while (!deadline.hasExpired());

    return false;
}

void SignalWaiter::timedOut()
{
    m_timedOut = true;
    m_loop.quit();
}

void SignalWaiter::signalEmmited()
{
    m_timedOut = false;
    m_loop.quit();
}
