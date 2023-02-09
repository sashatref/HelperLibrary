#pragma once

#include "extendedwidget.h"

namespace Ui {
class MakePasswordForm;
}

class HELPERLIBRARY_EXPORT MakePasswordForm : public ExtendedWidget
{
    Q_OBJECT
public:
    explicit MakePasswordForm(QWidget *parent = 0);
    ~MakePasswordForm();

private slots:
    void on_copyButton_clicked();
    void on_generateButton_clicked();

private:
    Ui::MakePasswordForm *ui;

public:
    virtual QVariant saveWidgetState() const override;
    virtual void loadWidgetState(const QVariant &_state) override;
};
