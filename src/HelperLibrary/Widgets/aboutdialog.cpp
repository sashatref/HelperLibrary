#include "aboutdialog.h"
#include "ui_aboutdialog.h"

namespace HelperLibraryNS
{

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);

//    ui->versionLineEdit->setText(qApp->applicationVersion());
//    ui->compileTimeLineEdit->setText(Utils::getCompileDateTime());
}

AboutDialog::~AboutDialog()
{
    delete ui;
}

void AboutDialog::setInfo(const QString &_appName, const QString &_appVer, const QString &_buildTime)
{
    setAppName(_appName);
    setAppVer(_appVer);
    setAppBuildTime(_buildTime);
}

void AboutDialog::setAppName(const QString &_name)
{
    ui->appNameEdit->setText(_name);
}

void AboutDialog::setAppVer(const QString &_ver)
{
    ui->versionLineEdit->setText(_ver);
}

void AboutDialog::setAppBuildTime(const QString &_buildTime)
{
    ui->compileTimeLineEdit->setText(_buildTime);
}

}
