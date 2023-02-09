#include "SimplePresetCombo.h"
#include "ui_SimplePresetCombo.h"
#include "../../Styles/iconsenum.h"

namespace HelperLibraryNS
{

SimplePresetCombo::SimplePresetCombo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SimplePresetCombo)
{
    ui->setupUi(this);

    ui->saveBtn->setIcon(IconsEnum::getIcon(IconsEnum::SP_Save1));
    ui->removeBtn->setIcon(IconsEnum::getIcon(IconsEnum::SP_Delete1));

    ui->comboBox->lineEdit()->setPlaceholderText(tr("Пусто"));
    ui->comboBox->setAutoCompletionCaseSensitivity(Qt::CaseSensitive);
    ui->comboBox->lineEdit()->setFont(ui->comboBox->font());
}

SimplePresetCombo::~SimplePresetCombo()
{
    delete ui;
}

void SimplePresetCombo::loadPresets(const QVariantMap &_m, const QString &_currentPreset)
{
    ui->comboBox->clear();

    for(auto it = _m.begin(); it != _m.end(); ++it)
    {
        addPreset(it.key(), it.value());
    }

    QSignalBlocker lock(ui->comboBox);
    ui->comboBox->setCurrentText(_currentPreset);
}

QVariantMap SimplePresetCombo::savePresets() const
{
    QVariantMap out;

    for(int i = 0; i < ui->comboBox->count(); i++)
    {
        out[ui->comboBox->itemText(i)] = ui->comboBox->itemData(i);
    }

    return out;
}

void SimplePresetCombo::addPreset(const QString &_name, const QVariant &_data)
{
    QSignalBlocker lock(ui->comboBox);
    ui->comboBox->addItem(_name, _data);
    ui->comboBox->setCurrentText(_name);
}

void SimplePresetCombo::on_saveBtn_clicked()
{
    QString presetName = ui->comboBox->currentText();

    for(int i = 0 ; i < ui->comboBox->count(); i++)
    {
        if(ui->comboBox->itemText(i) == presetName)
        {
            int res = QMessageBox::question(this, tr("Перезаписать?"), tr("Предустановка [%1] существует. Перезаписать её?").arg(presetName));
            if(res == QMessageBox::No)
            {
                return;
            }

            QSignalBlocker lock(ui->comboBox);
            ui->comboBox->removeItem(i);
            break;
        }
    }

    emit needSaveItem(presetName);

    QMessageBox::information(this, tr("Успешно"), tr("Предустановка [%1] сохранена").arg(presetName));
}

void SimplePresetCombo::on_removeBtn_clicked()
{
    QString presetName = ui->comboBox->currentText();
    if(QMessageBox::question(this, tr("Удалить?"), tr("Удалить предустановку [%1]?").arg(presetName)) == QMessageBox::Yes)
    {
        QSignalBlocker lock(ui->comboBox);
        ui->comboBox->removeItem(ui->comboBox->currentIndex());
        ui->comboBox->setCurrentText("");
    }
}

void SimplePresetCombo::on_comboBox_currentIndexChanged(int /*index*/)
{
    emit loadPreset(ui->comboBox->currentData(Qt::UserRole));
}


}

