#pragma once

#include <QDialog>
#include <QRadioButton>
#include "filterwidgetconf.h"

namespace Ui {
class FilterWidgetConfigDialog;
}

class FilterWidgetConfigDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FilterWidgetConfigDialog(QWidget *parent = nullptr);
    ~FilterWidgetConfigDialog();

    void setConfig(const HelperLibraryNS::FilterWidgetConf &_conf);

    HelperLibraryNS::FilterWidgetConf getConfig();

signals:
    void clearHistory();

private slots:
    void on_clearHistory_clicked();

    void on_applyButton_clicked();

    void on_closeButton_clicked();

private:
    QList<QRadioButton*> rbList();

    Ui::FilterWidgetConfigDialog *ui;
};

