#pragma once

#include <QSystemTrayIcon>
#include <QAction>
#include "../../export.h"

class QMainWindow;

/*!
 * \brief The TrayMenu class
    Расширенная версия класса QSystemTrayIcon
    Добавляет в программу возможность сворачиваться в трей, добавлять свои QAction
    в контекстное меню иконки в трее.
 */

class HELPERLIBRARY_EXPORT TrayMenu : public QSystemTrayIcon
{
    Q_OBJECT
public:
    TrayMenu(QMainWindow *mainWindow, const QIcon &_icon = QIcon());
    virtual ~TrayMenu();

    void addAction(QAction *_action);

public slots:
    void minimize();
    void showMainWindow();

protected:
    bool eventFilter(QObject *obj, QEvent *event);

private slots:
    void onExitMenuClicked();
    void onMaximizeMenuClicked();
    void onTrayActivated(QSystemTrayIcon::ActivationReason _reason);

private:
    QMap<int, QAction*> m_actionList;

    QMenu *m_menu;
    QAction *m_exitAction;
    QAction *m_maximizeAction;
    QMainWindow *m_mainWindow;

    Qt::WindowStates m_prevWindowState = Qt::WindowActive;
    QByteArray m_state;

    void retranslate();
};

