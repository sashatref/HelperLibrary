#include "extendeddialog.h"
#include "../Events/settingchangeevent.h"



ExtendedDialog::ExtendedDialog(QWidget *_parent):
    QDialog(_parent)
{

}

void ExtendedDialog::updateLanguage()
{

}

void ExtendedDialog::updateStyle()
{

}

void ExtendedDialog::registerCustomTypes()
{

}

QString ExtendedDialog::getWidgetUniqueName() const
{
    return objectName();
}

void ExtendedDialog::initAll()
{
    registerCustomTypes();
    initUiComponets();
    initConnections();
    updateStyle();
    settingsChanged();
}

void ExtendedDialog::changeEvent(QEvent *event)
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

    QDialog::changeEvent(event);
}

void ExtendedDialog::closeEvent(QCloseEvent * /*event*/)
{
    emitSaveFunc();
}

bool ExtendedDialog::event(QEvent *event)
{
    if(event->type() == SettingChangeEvent::type())
    {
        settingsChanged();
        return true;
    }

    return QWidget::event(event);
}

void ExtendedDialog::initUiComponets()
{

}

void ExtendedDialog::initConnections()
{

}

void ExtendedDialog::settingsChanged()
{

}


void ExtendedDialog::accept()
{
    emitSaveFunc();
    QDialog::accept();
}

void ExtendedDialog::reject()
{
    emitSaveFunc();
    QDialog::reject();
}
