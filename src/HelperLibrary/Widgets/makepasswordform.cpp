#include "makepasswordform.h"
#include "ui_makepasswordform.h"
#include "../functions.h"

MakePasswordForm::MakePasswordForm(QWidget *parent) :
    ExtendedWidget  (parent),
    ui              (new Ui::MakePasswordForm)
{
    ui->setupUi(this);
}

MakePasswordForm::~MakePasswordForm()
{
    delete ui;
}

void MakePasswordForm::on_copyButton_clicked()
{
    qApp->clipboard()->setText(ui->passwordEdit->text());

    QToolTip::showText(QCursor::pos(),
                       tr("Пароль <%1> скопирован в буфер обмена").arg(ui->passwordEdit->text()));
}

void MakePasswordForm::on_generateButton_clicked()
{
    ui->passwordEdit->setText(Text::getRandomString(
                                  ui->minSizeSpin->value(),
                                  ui->maxSizeSpin->value()));
}


QVariant MakePasswordForm::saveWidgetState() const
{
    LayoutSaver saver;
    saver.saveGeometry(this, "geometry");
    saver.save(ui->minSizeSpin->value(), "min");
    saver.save(ui->maxSizeSpin->value(), "max");

    return saver;
}

void MakePasswordForm::loadWidgetState(const QVariant &_state)
{
    const LayoutSaver saver = _state.toMap();
    saver.load(this, "geometry");
    saver.load(ui->minSizeSpin, &QSpinBox::setValue, "min");
    saver.load(ui->maxSizeSpin, &QSpinBox::setValue, "max");
}

