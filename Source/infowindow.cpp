#include "infowindow.h"
#include "ui_infowindow.h"

InfoWindow::InfoWindow(const QString &_text, const QString &_caption, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InfoWindow)
{
    ui->setupUi(this);
    setWindowTitle(_caption);
    ui->textEdit->setText(_text);
}

InfoWindow::~InfoWindow()
{
    delete ui;
}

void InfoWindow::on_closeButton_clicked()
{
    accept();
}
