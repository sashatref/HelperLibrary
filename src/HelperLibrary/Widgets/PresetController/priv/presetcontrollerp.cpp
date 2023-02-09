#include "presetcontrollerp.h"
#include "ui_presetcontrollerform.h"
#include "Styles/iconsenum.h"
#include "helperscontainter.h"
#include "Widgets/SearchForm/searchform.h"
#include "Widgets/selectlistdialog/selectlistdialog.h"

namespace HelperLibraryNS
{
PresetControllerP::PresetControllerP(PresetControllerForm *_q):
    QObject(_q),
    q(_q)
{
    m_searcher = new ListWidgetSearcher(this, nullptr);
    m_searcher->setTitle(tr("Список предустановок"));
}

void PresetControllerP::presetListContextMenuSlot(const QPoint &_pos)
{
    if(q->ui->listWidget->selectedItems().size() == 0)
    {
        return;
    }

    QMenu menu;
    menu.addAction(IconsEnum::getIcon(IconsEnum::SP_Apply2),
                tr("Загрузить"), this, &PresetControllerP::loadPresetSlot);
    menu.addSeparator();
    menu.addAction(IconsEnum::getIcon(IconsEnum::SP_Minus2),
                   tr("Удалить"), this, &PresetControllerP::removeSelectedSlot);

    menu.exec(q->ui->listWidget->viewport()->mapToGlobal(_pos));
}

void PresetControllerP::savePresetSlot()
{
    QListWidgetItem *selected = getSelectedItem();
    QString presetName;

    //проверяем есть ли выбранный престет
    //если есть, то подставляем его имя в диалог ввода текста
    if(selected != nullptr)
    {
        presetName = selected->data(presetNameRole).toString();
    }

    bool isOk = false;

    //получаем новое имя пресета
    QString newPreset = QInputDialog::getText(q, tr("Имя предустановки"),
                                              tr("Введите имя предустановки"),
                                              QLineEdit::Normal,
                                              presetName, &isOk);
    if(!isOk)
    {
        return;
    }

    if(newPreset.isEmpty())
    {
        QMessageBox::warning(q, tr("Пусто"), tr("Название предустановки не может быть пустым"));
        return;
    }

    //кидаем событие сохранения пресета, чтоб получить заполненый QVariant
    bool isSaveOk = true;
    QVariant presetData;
    emit q->savePreset(newPreset, presetData, isSaveOk);

    if(!isSaveOk) //если пользователь отменил сохранение, то выходим
    {
        return;
    }

    //если имя нового пресета совпадает со старым, то просто обновляем запись
    if(QListWidgetItem *existItem = findItemWithName(newPreset))
    {
        int res = QMessageBox::question(q, tr("Перезаписать?"),
                                        tr("Предустановка [%1] уже есть в списке, перезаписать?")
                                        .arg(newPreset));
        if(res == QMessageBox::No)
        {
            return;
        } else
        {
            updateListItem(existItem, presetData, newPreset);
            return;
        }
    }

    //если не совпадает, то добавляем новую
    addListItem(newPreset, presetData);

    q->presetListUpdated(savePresets());
}

void PresetControllerP::loadPresetSlot()
{
    QListWidgetItem *selected = getSelectedItem();
    if(selected == nullptr)
    {
        QMessageBox::information(q, tr("Ошибка"), tr("Необходимо выбрать один элемент из списка"));
        return;
    }

    const QString presetName = selected->data(presetNameRole).toString();

    int res = QMessageBox::question(q,
                                    tr("Загрузить"),
                                    tr("Уверены, что хотите загрузить предустановку [%1] ?")
                                    .arg(presetName));
    if(res == QMessageBox::Yes)
    {
        const QVariant data = selected->data(presetDataRole);
        emit q->loadPreset(presetName, data);
    }
}

void PresetControllerP::removeSelectedSlot()
{
    QList<QListWidgetItem*> selected = q->ui->listWidget->selectedItems();

    if(selected.size() == 0)
    {
        QMessageBox::warning(q, tr("Внимание!"), tr("Необходимо выбрать хотя бы один элемент списка"));
        return;
    }

    QStringList names;
    for(auto *it : selected)
    {
        names << it->data(presetNameRole).toString();
    }

    if(QMessageBox::question(q,
                             tr("Уверены?"),
                             tr("Удалить выбранные записи?\n\n%1")
                             .arg(names.join("\n"))) == QMessageBox::No)
    {
        return;
    }

    qDeleteAll(selected);

    emit q->presetListUpdated(savePresets());
}

void PresetControllerP::loadFromFileSlot()
{
    QString path = QFileDialog::getOpenFileName(q,
                                                tr("Выберите файл"),
                                                m_lastPath,
                                                m_presetDialogFilter);
    if(path.isEmpty())
    {
        return;
    }

    m_lastPath = path;

    LayoutSaver saver;

    //загружаем все предустановки из файла
    if(saver.loadFromFile(m_lastPath))
    {
        //даем пользователю выбрать, какие предустановки загружать
        SelectListDialog dialog(q);
        dialog.setData(saver["presets"].toMap());
        if(dialog.exec() != QDialog::Accepted)
        {
            return;
        }

        QVariantMap presets = dialog.getSelectedDataAsMap(); //список выбранных предустановок

        QStringList alreadyExistsPresets;

        //формируем список пересекающихся имен из файла и существующих пресетов
        for(int i = 0 ; i < q->ui->listWidget->count(); i++)
        {
            const QString name = q->ui->listWidget->item(i)->data(presetNameRole).toString();
            if(presets.contains(name))
            {
                alreadyExistsPresets << name;
            }
        }

        //если список не пустой, выдаем пользователю предупреждение о перезаписи.
        if(alreadyExistsPresets.size())
        {
            int res = QMessageBox::question(q, tr("Внимание!"),
                                  tr("Данные предустановки будут перезаписаны:\n\n%1")
                                  .arg(alreadyExistsPresets.join("\n")));
            if(res != QMessageBox::Yes)
            {
                return;
            }
        }

        //добавляем предустановки в список
        addPresets(presets);
        QMessageBox::information(q, tr("Успешно"),
                                 tr("Предустановки успешно загружены из файла [%1]\n\n%2")
                                 .arg(m_lastPath)
                                 .arg(presets.keys().join("\n")));

    } else
    {
        QMessageBox::warning(q, tr("Ошибка"),
                             tr("Ошибка загрузки предустановок из файла [%1]").arg(m_lastPath));
    }
}

void PresetControllerP::saveToFileSlot()
{
    if(q->ui->listWidget->selectedItems().size() == 0)
    {
        QMessageBox::warning(q,
                             tr("Ошибка"),
                             tr("Необходимо выбрать хотя бы один элемент списка предустановок"));
        return;
    }

    QString path = QFileDialog::getSaveFileName(q,
                                                tr("Выберите файл"),
                                                m_lastPath,
                                                m_presetDialogFilter);
    if(path.isEmpty())
    {
        return;
    }

    m_lastPath = path;

    LayoutSaver saver;

    const QVariantMap presets = saveSelectedPresets();
    saver["presets"] = presets;
    if(saver.saveToFile(m_lastPath))
    {
        QMessageBox::information(q, tr("Успешно"),
                                 tr("Предустановки успешно сохранены в файл [%1]\n\n%2")
                                 .arg(m_lastPath)
                                 .arg(presets.keys().join("\n")));
    } else
    {
        QMessageBox::warning(q, tr("Ошибка"),
                             tr("Ошибка сохранения предустановок в файл [%1]").arg(m_lastPath));
    }
}

void PresetControllerP::showSearchForm()
{
    m_searcher->createAndShowSearchForm();
}

void PresetControllerP::loadPresets(const QVariantMap &_presets)
{
    q->ui->listWidget->clear();
    addPresets(_presets);
}

void PresetControllerP::addPresets(const QVariantMap &_presets)
{
    //загружаем список предусатновкой из QVariantMap

    QListWidget *lw = q->ui->listWidget;

    for(auto it = _presets.begin(); it != _presets.end(); it++)
    {
        addListItem(it.key(), it.value());
    }

    lw->update();

    emit q->presetListUpdated(savePresets());
}

QVariantMap PresetControllerP::savePresets() const
{
    //сохраняем список предустановок в QVariantMap
    QVariantMap out;

    QListWidget *lw = q->ui->listWidget;

    const int count = lw->count();

    for(int i = 0 ; i < count ; i++)
    {
        QListWidgetItem *lwItem = lw->item(i);
        out[lwItem->data(presetNameRole).toString()] = lwItem->data(presetDataRole);
    }

    return out;
}

QVariantMap PresetControllerP::saveSelectedPresets() const
{
    //сохраняем список выбранных предустановок в QVariantMap
    QVariantMap out;

    QList<QListWidgetItem*> selected = q->ui->listWidget->selectedItems();

    for(auto &lwItem : selected)
    {
        out[lwItem->data(presetNameRole).toString()] = lwItem->data(presetDataRole);
    }

    return out;
}

void PresetControllerP::addListItem(const QString &_preset, const QVariant &_value)
{
    QListWidget *lw = q->ui->listWidget;

    QListWidgetItem *lwItem = new QListWidgetItem();
    updateListItem(lwItem, _value, _preset);
    lw->addItem(lwItem);
}

void PresetControllerP::updateListItem(QListWidgetItem *_item, const QVariant &_value, const QString &_newPresetName)
{
    _item->setData(presetDataRole, QVariant::fromValue(_value));
    _item->setData(presetNameRole, _newPresetName);

//    QStringList tooltipList;

    //    for(ShortControlInfo &key : _value.keys())
    //    {
    //        tooltipList << key.controlName;
    //    }

    _item->setText(QString("%1")
                   .arg(_newPresetName));

}

QListWidgetItem *PresetControllerP::findItemWithName(const QString &_name)
{
    for(int i = 0 ; i < q->ui->listWidget->count(); i++)
    {
        QListWidgetItem *item = q->ui->listWidget->item(i);

        if(item->data(presetNameRole).toString() == _name)
        {
            return item;
        }
    }

    return nullptr;
}

QListWidgetItem *PresetControllerP::getSelectedItem()
{
    QList<QListWidgetItem*> selcted = q->ui->listWidget->selectedItems();
    if(selcted.size())
    {
        return selcted.first();
    }

    return nullptr;
}

bool PresetControllerP::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == q->ui->listWidget)
    {
        if(event->type() == QEvent::KeyPress)
        {
            QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
            if(keyEvent->key() == Qt::Key_Delete)
            {
                removeSelectedSlot();
            }
        }
    }

    return QObject::eventFilter(watched, event);
}

}


