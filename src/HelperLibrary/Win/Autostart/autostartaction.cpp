#include "autostartaction.h"
#include "autostartwrapper.h"

namespace HelperLibraryNS
{
    AutostartAction::AutostartAction(const QString &_appName, const QStringList &_args, QObject *_parent):
        QAction(_parent),
        p(new AutoStartWrapper(_appName, _args))
    {
        connect(this, &AutostartAction::triggered, this, [=](bool b)
        {
            p->setAutoStart(b);
            setToolTip(p->getAutoStartParam());
        });

        setCheckable(true);

        const QString autostartParam = p->getAutoStartParam();
        setToolTip(autostartParam);
        setChecked(!autostartParam.isEmpty());

        setText(tr("Автозапуск"));
    }

    AutostartAction::~AutostartAction()
    {
        delete p;
    }


    bool AutostartAction::event(QEvent *event)
    {
        return QAction::event(event);
    }
}



