#pragma once

#include <QMainWindow>
#include "../export.h"
#include "isavewidget.h"


struct ExtendedMainWindowP;

class HELPERLIBRARY_EXPORT ExtendedMainWindow :
        public QMainWindow,
        public ISaveWidget
{
    Q_OBJECT
public:
    ExtendedMainWindow(QWidget *_parent = 0);
    virtual ~ExtendedMainWindow();

    void setPromtToClose(bool _isPromt);    // будет ли выдавать запрос при закрытие формы
    bool getPromtToClose() const;

    virtual void updateLanguage();
    virtual void updateStyle();

    virtual QString getWidgetUniqueName() const override;

    void initAll(); //registerCustomTypes();
                    //initUiComponets();
                    //initConnections();
                    //updateStyle();
                    //settingsChanged();

    virtual void registerCustomTypes();

    void registerIndependentWindow(QWidget *_independentWidnow);    //зарегестрировать окно без родителя

signals:
    void closeSignal();

protected:
    virtual void changeEvent(QEvent *event) override;
    virtual void closeEvent(QCloseEvent *event) override;
    virtual bool event(QEvent *event) override;

    virtual void initUiComponets();
    virtual void initConnections();
    virtual void settingsChanged();

    void closeIndependentWindows(); //закрывает все окна без родителя

private:
    ExtendedMainWindowP *p;
};

QVariant HELPERLIBRARY_EXPORT saveWidgetState(const ExtendedMainWindow *_mw);
void HELPERLIBRARY_EXPORT loadWidgetState(ExtendedMainWindow *_mw, const QVariant &_val);

