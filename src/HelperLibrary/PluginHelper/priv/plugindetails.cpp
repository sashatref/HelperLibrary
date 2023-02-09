#include "../../project_pch.h"
#include "plugindetails.h"
#include "ui_plugindetails.h"

namespace HelperLibraryNS
{

PluginDetails::PluginDetails(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PluginDetails)
{
    ui->setupUi(this);
}

void PluginDetails::initValues(const QString &_name,
                               bool _isEnable,
                               bool _isLoaded,
                               const QString &_version,
                               const QString &_uniqueName,
                               const QString &_description)
{
    ui->nameEdit->setText(_name);
    ui->enableCheck->setChecked(_isEnable);
    ui->loadCheck->setChecked(_isLoaded);
    ui->versionEdit->setText(_version);
    ui->uniqueNameEdit->setText(_uniqueName);
    ui->descriptionEdit->setText(_description);
}

PluginDetails::~PluginDetails()
{
    delete ui;
}

void PluginDetails::on_closeButton_clicked()
{
    close();
}

}
