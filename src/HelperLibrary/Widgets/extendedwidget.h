#pragma once

#include <QWidget>

#include "../export.h"
#include "isavewidget.h"

class HELPERLIBRARY_EXPORT ExtendedWidget : public QWidget, public ISaveWidget
{
    Q_OBJECT
public:
    ExtendedWidget(QWidget *_parent = 0);

    virtual void updateLanguage();
    virtual void updateStyle();
    virtual void registerCustomTypes();

    virtual QString getWidgetUniqueName() const override;

    void initAll(); //registerCustomTypes();
                    //initUiComponets();
                    //initConnections();
                    //updateStyle();
                    //settingsChanged();

protected:
    virtual void changeEvent(QEvent *event) override;
    virtual void closeEvent(QCloseEvent *event) override;
    virtual bool event(QEvent *event) override;

    virtual void initUiComponets();
    virtual void initConnections();
    virtual void settingsChanged();
};

