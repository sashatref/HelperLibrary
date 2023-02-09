#include "infowindow.h"
#include "ui_infowindow.h"

#include "widgethelper.h"
#include "../Exceptions/userexception.h"

#include <QDesktopWidget>

InfoWindow::InfoWindow(const QString &_text, const QString &_caption, const QSize &_formSize, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InfoWindow)
{
    ui->setupUi(this);
    setWindowTitle(_caption);
    ui->textEdit->setText(_text);

    WidgetHelper::setWidgetOnScreenCenter(this, parent, _formSize.width(), _formSize.height());
}

InfoWindow::InfoWindow(QWidget *_parent, const QString &_text) :
    QDialog(_parent),
    ui(new Ui::InfoWindow)
{
    ui->setupUi(this);
    setWindowTitle("Info");
    ui->textEdit->setText(_text);

    WidgetHelper::setWidgetOnScreenCenter(this, _parent, 600, 300);
}

InfoWindow::InfoWindow(const HelperLibrary::UserExceptions::BaseException &e, QWidget *_parent):
    QDialog(_parent),
    ui(new Ui::InfoWindow)
{
    ui->setupUi(this);
    setWindowTitle("Info");

    ui->textEdit->setText(e.getText() + "\n" + e.getStackTraceList().join("\n"));

    QDesktopWidget dWidget;
    int screenNum = dWidget.screenNumber(_parent);
    const QRect geometry = dWidget.availableGeometry(screenNum);

    const int widht = geometry.width() - 300;
    const int height = geometry.height() - 300;

    WidgetHelper::setWidgetOnScreenCenter(this, _parent, widht, height);
}

InfoWindow::~InfoWindow()
{
    delete ui;
}

void InfoWindow::on_closeButton_clicked()
{
    accept();
}
