#include "../project_pch.h"
#include "extendedwidget.h"
#include "../Events/settingchangeevent.h"

ExtendedWidget::ExtendedWidget(QWidget *_parent):
    QWidget(_parent)
{
    //QApplication::postEvent(this, new QEvent(QEvent::StyleChange));
}

void ExtendedWidget::updateLanguage()
{

}

void ExtendedWidget::updateStyle()
{

}


void ExtendedWidget::changeEvent(QEvent *event)
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

    QWidget::changeEvent(event);
}


QString ExtendedWidget::getWidgetUniqueName() const
{
    return objectName();
}

void ExtendedWidget::initAll()
{
    registerCustomTypes();
    initUiComponets();
    initConnections();
    updateStyle();
    settingsChanged();
}


void ExtendedWidget::closeEvent(QCloseEvent * /*event*/)
{
    emitSaveFunc();
}

void ExtendedWidget::initUiComponets()
{

}

void ExtendedWidget::initConnections()
{

}

void ExtendedWidget::registerCustomTypes()
{

}

void ExtendedWidget::settingsChanged()
{

}

bool ExtendedWidget::event(QEvent *event)
{
    if(event->type() == SettingChangeEvent::type())
    {
        settingsChanged();
        return true;
    }

    return QWidget::event(event);
}
