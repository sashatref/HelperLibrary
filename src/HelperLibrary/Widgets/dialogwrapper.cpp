#include "dialogwrapper.h"
#include "ui_dialogwrapper.h"

#include "Styles/iconsenum.h"

DialogWrapper::DialogWrapper(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogWrapper)
{
    ui->setupUi(this);

    ui->applyBtn->setIcon(IconsEnum::applyButtonIcon());
    ui->closeBtn->setIcon(IconsEnum::closeButtonIcon());
}

DialogWrapper::~DialogWrapper()
{
    delete ui;
}

void DialogWrapper::setWidget(QWidget *_w)
{
    m_widget = _w;
    ui->verticalLayout->addWidget(_w);
}

QWidget *DialogWrapper::getWidget()
{
    return m_widget;
}

void DialogWrapper::on_applyBtn_clicked()
{
    accept();
}

void DialogWrapper::on_closeBtn_clicked()
{
    reject();
}
