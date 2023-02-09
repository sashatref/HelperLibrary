#include "project_pch.h"
#include "keyboardlayoutviewer.h"

//#ifdef Q_OS_LINUX
//    #include "../Linux/XKeyboard.h"
//#endif

QString getCurrentLayout()
{
#ifdef Q_OS_WIN
    HKL hkl_id = GetKeyboardLayout(0);
    int lang_id =  LOWORD(hkl_id);
    wchar_t buf[11] = {0};
    GetLocaleInfo( MAKELCID(lang_id, SORT_DEFAULT),
                   LOCALE_SISO639LANGNAME,
                   buf,
                   10);

    return QString::fromWCharArray(buf).toUpper();
#endif // Q_OS_WIN

#ifdef Q_OS_LINUX
//    XKeyboard xkb;
//    return QString("%1")
//            .arg(xkb.currentGroupSymbol().c_str())
            /*.arg(xkb.currentGroupName().c_str())*/;
    return QString();
#endif
}

KeyboardLayoutViewer::KeyboardLayoutViewer(QObject *_parent):
    QAction(_parent)
{
    QFont f = font();
    f.setPixelSize(30);
    setFont(f);

    this->setEnabled(false);
    this->setToolTip(tr("Текущая раскладка клавиатуры"));
    this->setText(getCurrentLayout());
}

void KeyboardLayoutViewer::handleNativeMessage(const QByteArray &eventType, void *message, long * /*result*/)
{
    Q_UNUSED(eventType);

#ifdef Q_OS_WIN
    MSG* msg = reinterpret_cast<MSG*>(message);
    if(msg && msg->message == WM_INPUTLANGCHANGE)
    {
        this->setText(getCurrentLayout());
    }
#endif // Q_OS_WIN

#ifdef Q_OS_LINUX
//    xcb_generic_event_t *event = reinterpret_cast<xcb_generic_event_t*>(message);
//    switch(event->response_type)
//    {
//    case XCB_KEY_PRESS:
//        qDebug() << "ButtonPress";
//        break;
//    default:
//        break;
//    }
#endif //Q_OS_LINUX
}

bool KeyboardLayoutViewer::event(QEvent *event)
{
    if(event->type() == QEvent::LanguageChange)
    {
        setToolTip(tr("Текущая раскладка клавиатуры"));
    }

    return QObject::event(event);
}
