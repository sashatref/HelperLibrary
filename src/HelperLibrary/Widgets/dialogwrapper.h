#pragma once

#include "../export.h"

#include <QDialog>

namespace Ui {
class DialogWrapper;
}

class HELPERLIBRARY_EXPORT DialogWrapper : public QDialog
{
    Q_OBJECT
public:
    explicit DialogWrapper(QWidget *parent = nullptr);
    ~DialogWrapper();

    void setWidget(QWidget *_w);
    QWidget *getWidget();

private slots:
    void on_applyBtn_clicked();
    void on_closeBtn_clicked();

private:
    Ui::DialogWrapper *ui;
    QWidget *m_widget = nullptr;
};

