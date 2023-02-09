#pragma once

#include <QObject>
#include <QTimer>
#include <QEventLoop>
#include <QFuture>

#include "export.h"

class HELPERLIBRARY_EXPORT SignalWaiter : public QObject
{
    Q_OBJECT
public:

    enum ExitStatus
    {
        esSuccess,
        esTimedOut,
        esExprReturnTrue
    };

    template <class ClassType, class Func>
    SignalWaiter(ClassType *_object, Func _func, Qt::ConnectionType _type = Qt::AutoConnection)
    {
        connect(_object, _func, this, &SignalWaiter::signalEmmited, _type);
        connect(&m_timer, &QTimer::timeout, this, &SignalWaiter::timedOut, _type);
    }

    ~SignalWaiter();

    bool wait(int _msec);


    template<class ClassType, class Func>
    ExitStatus wait(int _msecTotal, ClassType *_obj, Func _func, int _exprCheckInterval)
    {
        auto res = std::bind(_func, _obj);
        return wait(_msecTotal, res, _exprCheckInterval);
    }

    /*!
     * \brief wait
     * \param _msecTotal
     * \param _checkExpr return bool if need to stop now
     * \param _exprCheckInterval    interval for execute _checkExpr
     * \return
     */

    ExitStatus wait(int _msecTotal, std::function<bool()> _checkExpr, int _exprCheckInterval);

    // return false if timedout
    // крутим EventLoop пока _checkExpr не вернет true или не закончится время _msecTotal
    static bool waitExp(int _msecTotal, int _exprCheckInterval, std::function<bool()> _checkExpr);


    template<class Type>
    static bool waitFuture(QFuture<Type> _future, int _timeout = 30000, int _checkInterval = 50)
    {
        return SignalWaiter::waitExp(_timeout, _checkInterval, [&]
        {
            return _future.isFinished();
        });
    }

private slots:
    void timedOut();

    void signalEmmited();

private:
    QEventLoop m_loop;
    QTimer m_timer;
    bool m_timedOut;
};
