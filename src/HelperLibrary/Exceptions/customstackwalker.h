#pragma once

#include <QtCore/qglobal.h>
#include <QDebug>
#include "StackWalker.h"

class CustomStackWalker : public StackWalker
{
public:
    CustomStackWalker();

    QString getTraceText() const;
    QStringList getTraceList() const;

protected:
    virtual void OnCallstackEntry(CallstackEntryType eType, CallstackEntry &entry) Q_DECL_OVERRIDE;
    virtual void OnOutput(LPCSTR /*szText*/) Q_DECL_OVERRIDE;

private:
    QStringList m_result;
};

