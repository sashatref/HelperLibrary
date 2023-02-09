#pragma once

#include <QDialog>

#include "../export.h"
#include "isavewidget.h"
#include "../igadget.h"

class HELPERLIBRARY_EXPORT ExtendedDialog : public QDialog, public ISaveWidget
{
    Q_OBJECT
public:
    ExtendedDialog(QWidget *_parent = 0);

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

    // QDialog interface
public slots:
    virtual void accept() override;
    virtual void reject() override;
};

