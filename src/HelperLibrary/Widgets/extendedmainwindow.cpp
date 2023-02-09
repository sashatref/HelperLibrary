#include "../project_pch.h"
#include "extendedmainwindow.h"
#include "../Events/settingchangeevent.h"
#include "independentwidgetholder.h"

struct ExtendedMainWindowP
{
    ExtendedMainWindowP():
        m_promtToClose(true)
    {

    }

    HelperLibraryNS::IndependentWidgetHolder m_widgetHolder;
    bool m_promtToClose;
};

ExtendedMainWindow::ExtendedMainWindow(QWidget *_parent):
    QMainWindow(_parent),
    p(new ExtendedMainWindowP())
{

}

ExtendedMainWindow::~ExtendedMainWindow()
{
    delete p;
}

void ExtendedMainWindow::updateLanguage()
{

}

void ExtendedMainWindow::updateStyle()
{

}


void ExtendedMainWindow::changeEvent(QEvent *event)
{
    switch(event->type())
    {
    case QEvent::LanguageChange:
        updateLanguage();
        break;
    case QEvent::StyleChange:
        updateStyle();
        break;
    default:
        break;
    }

    QMainWindow::changeEvent(event);
}

bool ExtendedMainWindow::event(QEvent *event)
{
    if(event->type() == SettingChangeEvent::type())
    {
        settingsChanged();
    }

    return QMainWindow::event(event);
}

void ExtendedMainWindow::closeEvent(QCloseEvent *event)
{
    p->m_widgetHolder.closeIndependentWindows();

    if(p->m_promtToClose)
    {
        if(QMessageBox::question(this, tr("Выход"), tr("Закрыть программу?")) == QMessageBox::No)
        {
            event->ignore();
            return;
        }
    }

    emitSaveFunc();

    QMainWindow::closeEvent(event);

    emit closeSignal();
}

void ExtendedMainWindow::initUiComponets()
{

}

void ExtendedMainWindow::initConnections()
{

}

void ExtendedMainWindow::registerCustomTypes()
{

}

void ExtendedMainWindow::settingsChanged()
{

}

void ExtendedMainWindow::registerIndependentWindow(QWidget *_independentWidnow)
{
    p->m_widgetHolder.registerIndependentWindow(_independentWidnow);
}

void ExtendedMainWindow::closeIndependentWindows()
{
    p->m_widgetHolder.closeIndependentWindows();
}

void ExtendedMainWindow::setPromtToClose(bool _isPromt)
{
    p->m_promtToClose = _isPromt;
}

bool ExtendedMainWindow::getPromtToClose() const
{
    return p->m_promtToClose;
}


QString ExtendedMainWindow::getWidgetUniqueName() const
{
    return objectName();
}

void ExtendedMainWindow::initAll()
{
    registerCustomTypes();
    initUiComponets();
    initConnections();
    updateStyle();
    settingsChanged();
}

QVariant saveWidgetState(const ExtendedMainWindow *_mw)
{
    LayoutSaver saver;

    saver.save(dynamic_cast<const QMainWindow*>(_mw), "mw");
    saver.save(dynamic_cast<const ISaveWidget*>(_mw), "isavewidget");

    return saver.m();
}

void loadWidgetState(ExtendedMainWindow *_mw, const QVariant &_val)
{
    const LayoutSaver saver(_val.toMap());

    saver.load(dynamic_cast<QMainWindow*>(_mw), "mw");
    saver.load(dynamic_cast<ISaveWidget*>(_mw), "isavewidget");
}

