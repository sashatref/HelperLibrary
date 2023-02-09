#pragma once

#include <QAction>
#include "../export.h"

class HELPERLIBRARY_EXPORT KeyboardLayoutViewer : public QAction
{
    Q_OBJECT
public:
    KeyboardLayoutViewer(QObject *_parent = 0);

    void handleNativeMessage(const QByteArray &eventType, void *message, long *result);

    virtual bool event(QEvent *event) override;
};
