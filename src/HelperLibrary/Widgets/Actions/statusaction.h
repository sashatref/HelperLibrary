#pragma once

#include <QWidgetAction>
#include "../../export.h"

class QToolButton;

namespace HelperLibraryNS
{

class HELPERLIBRARY_EXPORT StatusAction : public QWidgetAction
{
public:
    StatusAction(QWidget *_parent);
    void setName(const QString &_name);

    void setAddInfo(const QString &_text);

public slots:
    void setOnlineStatus(bool _isOnline);

private slots:
    void buttonClickedSlot();

private:
    void updateText();

    QToolButton *m_button = nullptr;
    QString m_name;
    QString m_addInfo;
    bool m_isOnline = false;
};

}
