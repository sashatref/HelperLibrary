#include "resourceexplorerdialog.h"
#include "ui_resourceexplorerdialog.h"
#include "resourceexplorer.h"
#include "../Styles/iconsenum.h"

ResourceExplorerDialog::ResourceExplorerDialog(QWidget *parent) :
    ExtendedDialog  (parent),
    ui              (new Ui::ResourceExplorerDialog)
{
    ui->setupUi(this);

    connect(ui->widget, &ResourceExplorer::fileDoubleClicked, this, &ResourceExplorerDialog::accept);

    ui->applyButton->setIcon(IconsEnum::applyButtonIcon());
    ui->cancelButton->setIcon(IconsEnum::closeButtonIcon());
}

ResourceExplorerDialog::~ResourceExplorerDialog()
{
    delete ui;
}

void ResourceExplorerDialog::setSelectedFile(const QString &_file)
{
    ui->widget->setSelectedFile(_file);
}

QString ResourceExplorerDialog::getSelectedFile() const
{
    return ui->widget->getSelectedFile();
}

void ResourceExplorerDialog::on_applyButton_clicked()
{
    if(getSelectedFile().isEmpty())
    {
        QMessageBox::warning(this, tr("Ошибка"), tr("Выберите файл"));
        return;
    }

    accept();
}

void ResourceExplorerDialog::on_cancelButton_clicked()
{
    reject();
}

void ResourceExplorerDialog::loadState(const LayoutSaver &_saver)
{
    _saver.loadGeometry(this, "g");
    _saver.load(ui->widget, "widget");
}

void ResourceExplorerDialog::saveState(LayoutSaver &_saver) const
{
    _saver.saveGeometry(this, "g");
    _saver.save(ui->widget, "widget");
}


