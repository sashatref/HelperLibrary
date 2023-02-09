#include "filterwidgetconfigdialog.h"
#include "ui_filterwidgetconfigdialog.h"
#include "../../../Styles/iconsenum.h"

FilterWidgetConfigDialog::FilterWidgetConfigDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FilterWidgetConfigDialog)
{
    ui->setupUi(this);

    ui->applyButton->setIcon(IconsEnum::getIcon(IconsEnum::SP_Apply2));
    ui->closeButton->setIcon(IconsEnum::getIcon(QStyle::SP_DialogCloseButton));
    ui->clearHistory->setIcon(IconsEnum::getIcon(IconsEnum::SP_Erase1));
}

FilterWidgetConfigDialog::~FilterWidgetConfigDialog()
{
    delete ui;
}

void FilterWidgetConfigDialog::setConfig(const HelperLibraryNS::FilterWidgetConf &_conf)
{
    ui->registryCheckBox->setChecked(_conf.caseSensitivity);

    for(auto rb : rbList())
    {
        if(rb->property("pattern").toInt() == _conf.pattern)
        {
            rb->setChecked(true);
        }
    }
}

HelperLibraryNS::FilterWidgetConf FilterWidgetConfigDialog::getConfig()
{
    HelperLibraryNS::FilterWidgetConf out;

    out.caseSensitivity = (Qt::CaseSensitivity)ui->registryCheckBox->isChecked();

    for(auto rb : rbList())
    {
        if(rb->isChecked())
        {
            out.pattern = (QRegExp::PatternSyntax)rb->property("pattern").toInt();
        }
    }
    return out;
}

void FilterWidgetConfigDialog::on_clearHistory_clicked()
{
    emit clearHistory();
}

QList<QRadioButton *> FilterWidgetConfigDialog::rbList()
{
    return {
                ui->radioButton,
                ui->radioButton_2,
                ui->radioButton_3
    };
}

void FilterWidgetConfigDialog::on_applyButton_clicked()
{
    bool isChecked = false;

    for(auto rb : rbList())
    {
        if(rb->isChecked())
        {
            isChecked = true;
            break;
        }
    }

    if(!isChecked)
    {
        QMessageBox::warning(this, tr("Ошибка"), tr("Необходимо выбрать режим поиска"));
        return;
    }

    accept();
}

void FilterWidgetConfigDialog::on_closeButton_clicked()
{
    reject();
}
