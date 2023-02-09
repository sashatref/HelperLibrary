#pragma once

#include <QWidget>

namespace Ui {
class ShowIconsForm;
}

class ShowIconsForm : public QWidget
{
    Q_OBJECT

public:
    explicit ShowIconsForm(QWidget *parent = 0);
    ~ShowIconsForm();

    void initElements();

private:
    Ui::ShowIconsForm *ui;

    // QWidget interface
protected:
    virtual void changeEvent(QEvent *event) override;
private slots:
    void on_sizeSpinBox_valueChanged(int arg1);
};

