#include "statusaction.h"
#include "Widgets/infowindow.h"

namespace HelperLibraryNS
{

StatusAction::StatusAction(QWidget *_parent):
    QWidgetAction   (_parent)
{
    m_button = new QToolButton(_parent);
    m_button->setAutoRaise(true);
    m_button->setAutoFillBackground(true);
    m_button->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    m_button->setMinimumSize(24, 24);

    setDefaultWidget(m_button);

    connect(m_button, &QToolButton::clicked, this, &StatusAction::buttonClickedSlot);

    setOnlineStatus(false);
    updateText();
}

void StatusAction::setName(const QString &_name)
{
    m_name = _name;
    updateText();
}

void StatusAction::setAddInfo(const QString &_text)
{
    m_addInfo = _text;
    updateText();
}

void StatusAction::setOnlineStatus(bool _isOnline)
{
    m_isOnline = _isOnline;

    QColor c = _isOnline ? QColor(0x98FB98) : QColor(0xFA8072);

    m_button->setStyleSheet(QString("QToolButton {"
                                    "background-color: %1; "
                                    "border: 1px solid black;"
                                    "margin: 2px;}").arg(c.name()));

    updateText();
}

void StatusAction::buttonClickedSlot()
{
//    QMessageBox::information(m_button,
//                             tr("Подробнее"),
//                             m_button->toolTip());

    InfoWindow(m_button->toolTip()).exec();
}

void StatusAction::updateText()
{
    m_button->setText( m_name );

    if(m_addInfo.isEmpty())
    {
        QString tooltipText = QString("%1 [%2]")
                .arg( m_name )
                .arg( m_isOnline ? tr("подключен") : tr("отключен") );
        m_button->setToolTip(tooltipText);
    } else
    {
        m_button->setToolTip(m_addInfo);
    }


}

}
