#pragma once

#include "../../export.h"
#include <QAction>
#include <QStringList>

namespace HelperLibraryNS
{

class AutoStartWrapper;
class HELPERLIBRARY_EXPORT AutostartAction : public QAction
{
public:
    AutostartAction(const QString &_appName, const QStringList &_args, QObject *_parent = nullptr);
    ~AutostartAction();

private:
    AutoStartWrapper *p;

    // QObject interface
public:
    virtual bool event(QEvent *event) override;
};

}
