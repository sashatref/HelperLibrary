#include "traymenu.h"

#include <QMainWindow>

TrayMenu::TrayMenu(QMainWindow *mainWindow, const QIcon &_icon):
    QSystemTrayIcon         (mainWindow),
    m_menu                  (new QMenu()),
    m_mainWindow            (mainWindow)
{
    QSystemTrayIcon::setIcon(_icon);
    this->setContextMenu(m_menu);
    m_exitAction = new QAction(tr("Выход"), m_menu);
    m_maximizeAction = new QAction(tr("Показать"), m_menu);

    m_menu->addAction(m_maximizeAction);
    m_menu->addSeparator();
    m_menu->addAction(m_exitAction);
    m_menu->addSeparator();

    connect(m_exitAction, &QAction::triggered, this, &TrayMenu::onExitMenuClicked);
    connect(m_maximizeAction, &QAction::triggered, this, &TrayMenu::onMaximizeMenuClicked);
    connect(this, &TrayMenu::activated, this, &TrayMenu::onTrayActivated);

    m_mainWindow->installEventFilter(this);
    setToolTip(m_mainWindow->windowTitle());

    connect(m_mainWindow, &QMainWindow::windowTitleChanged, this, [=](const QString &title)
    {
        setToolTip(title);
    });
}

TrayMenu::~TrayMenu()
{
    m_mainWindow->removeEventFilter(this);
    delete m_exitAction;
    delete m_menu;
}

void TrayMenu::addAction(QAction *_action)
{
    m_menu->insertAction(m_maximizeAction, _action);
}


void TrayMenu::minimize()
{
    m_mainWindow->setWindowState(Qt::WindowMinimized);
}

bool TrayMenu::eventFilter(QObject *obj, QEvent *event)
{
    if(obj == m_mainWindow && event->type() == QEvent::WindowStateChange)
    {
        if(m_mainWindow->isMinimized())
        {
            this->show();
            m_mainWindow->hide();
        } else
        {
            m_prevWindowState = m_mainWindow->windowState();

#ifdef Q_OS_WIN
            SetForegroundWindow((HWND)m_mainWindow->winId());
#endif
        }
    } else if(obj == m_mainWindow && event->type() == QEvent::LanguageChange)
    {
        retranslate();
    }

    return m_mainWindow->eventFilter(obj, event);
}

void TrayMenu::onExitMenuClicked()
{
    m_mainWindow->close();
}

void TrayMenu::onMaximizeMenuClicked()
{
    showMainWindow();
}


void TrayMenu::onTrayActivated(QSystemTrayIcon::ActivationReason _reason)
{
    if(_reason == QSystemTrayIcon::Trigger)
    {
        showMainWindow();
    }
}

void TrayMenu::showMainWindow()
{
    this->hide();
    m_mainWindow->setWindowState(m_prevWindowState);
    m_mainWindow->show();
}

void TrayMenu::retranslate()
{
    m_exitAction->setText(tr("Выход"));
    m_maximizeAction->setText(tr("Показать"));
}
