#include "presetslist.h"
#include "ui_presetslist.h"
#include "extlist.h"

#include "../../Styles/iconsenum.h"

namespace HelperLibraryNS
{

PresetsList::PresetsList(QWidget *parent) :
    ExtendedWidget(parent),
    ui(new Ui::PresetsList)
{
    ui->setupUi(this);

    initAll();
}

PresetsList::~PresetsList()
{
    delete ui;
}

void PresetsList::setLoadBtnVisible(bool _isVisible)
{
    ui->loadBtn->setVisible(_isVisible);
}

int PresetsList::getLoadBtnVisible() const
{
    return ui->loadBtn->isVisible();
}

void PresetsList::loadPresets(const QStringList &_presets)
{
    ui->extList->lw()->clear();

    ui->extList->lw()->addItems(_presets);
}

QStringList PresetsList::savePresets() const
{
    QStringList out;

    for(int i = 0 ; i < ui->extList->lw()->count(); i++)
    {
        out << ui->extList->lw()->item(i)->text();
    }

    return out;
}

QString PresetsList::getSelectedPreset() const
{
    QList<QListWidgetItem*> selected = ui->extList->lw()->selectedItems();
    if(selected.size() == 0)
    {
        return QString();
    }

    return selected.first()->text();
}

void PresetsList::on_saveBtn_clicked()
{
    QListWidgetItem *selected = getSelectedItem();
    QString presetName;

    if(selected != nullptr)
    {
        presetName = selected->text();
    }

    bool isOk = false;

    QString newPreset = QInputDialog::getText(this, tr("Имя предустановки"),
                                              tr("Введите имя предустановки"),
                                              QLineEdit::Normal,
                                              presetName, &isOk);
    if(!isOk)
    {
        return;
    }

    if(newPreset.isEmpty())
    {
        QMessageBox::warning(this, tr("Пусто"), tr("Название предустановки не может быть пустым"));
        return;
    }

    if(presetName == newPreset)
    {
        int res = QMessageBox::question(this, tr("Перезаписать?"),
                                       tr("Предустановка [%1] уже есть в списке, перезаписать?")
                                        .arg(presetName));
        if(res == QMessageBox::No)
        {
            return;
        } else
        {
            emit savePreset(newPreset);
            return;
        }
    }

    emit savePreset(newPreset);


    ui->extList->lw()->addItem(newPreset);
}

void PresetsList::on_removeBtn_clicked()
{
    QListWidgetItem *selected = getSelectedItem();
    if(selected == nullptr)
    {
        return;
    }

    QString presetName = selected->text();

    int res = QMessageBox::question(this, tr("Удалить?"),
                                    tr("Удалить предустановку [%1]?").arg(presetName));
    if(res == QMessageBox::Yes)
    {
        emit removePreset(presetName);
        delete selected;
    }
}

void PresetsList::on_loadBtn_clicked()
{
    QListWidgetItem *selected = getSelectedItem();
    if(selected == nullptr)
    {
        return;
    }

    QString presetName = selected->text();

    int res = QMessageBox::question(this,
                                    tr("Загрузить"),
                                    tr("Уверены, что хотите загрузить предустановку [%1]?")
                                    .arg(presetName));
    if(res == QMessageBox::Yes)
    {
        emit loadPreset(presetName);
    }
}

void PresetsList::currentItemChangedSlot(QListWidgetItem *_current, QListWidgetItem * /*_prev*/)
{
    if(_current)
    {
        emit previewPreset(_current->text());
    }
}

QListWidgetItem *PresetsList::getSelectedItem()
{
    QList<QListWidgetItem*> selcted = ui->extList->lw()->selectedItems();
    if(selcted.size())
    {
        return selcted.first();
    }

    return nullptr;
}

void PresetsList::updateLanguage()
{
    ui->retranslateUi(this);
}

void PresetsList::updateStyle()
{
    ui->saveBtn->setIcon(IconsEnum::getIcon(IconsEnum::SP_Save1));
    ui->loadBtn->setIcon(IconsEnum::getIcon(IconsEnum::SP_Apply2));
    ui->removeBtn->setIcon(IconsEnum::getIcon(IconsEnum::SP_Minus2));
}

void PresetsList::initUiComponets()
{
    connect(ui->extList->lw(), &QListWidget::currentItemChanged, this, &PresetsList::currentItemChangedSlot);
}

void PresetsList::initConnections()
{
}

}


