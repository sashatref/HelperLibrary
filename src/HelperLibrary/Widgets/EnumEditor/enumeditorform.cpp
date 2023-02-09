#include "enumeditorform.h"
#include "ui_enumeditorform.h"
#include "Styles/iconsenum.h"

namespace HelperLibraryNS
{

EnumEditorForm::EnumEditorForm(QWidget *parent) :
    ExtendedDialog  (parent),
    ui              (new Ui::EnumEditorForm)
{
    ui->setupUi(this);

    initAll();
}

EnumEditorForm::~EnumEditorForm()
{
    delete ui;
}

void EnumEditorForm::setEnum(const QMap<int, QString> &_enum)
{
    QVariantMap vMap;

    for(auto it = _enum.begin(); it != _enum.end(); ++it)
    {
        vMap[QString::number(it.key())] = it.value();
    }

    ui->variantMapEditor->setVariantMap(vMap);
}

QMap<int, QString> EnumEditorForm::getEnum() const
{
    QMap<int, QString> out;

    QVariantMap vMap = ui->variantMapEditor->getVariantMap();

    for(auto it = vMap.begin(); it != vMap.end(); ++it)
    {
        out[it.key().toInt()] = it.value().toString();
    }

    return out;
}

void EnumEditorForm::setItems(const QList<QPair<int, QString> > &_items)
{
    ui->variantMapEditor->setItems(_items);
}

QList<QPair<int, QString> > EnumEditorForm::getItems() const
{
    return ui->variantMapEditor->getItems();
}

void EnumEditorForm::setControlDescription(const QString &_description)
{
    ui->applyBtn->setVisible(false);

    ui->plainTextEdit->setPlainText(_description);
    if(detectSeparators(_description))
    {
        on_parseStringBtn_clicked();
    }
}

bool EnumEditorForm::detectSeparators(const QString &_description)
{
    const QStringList separatosList = separators();

    QMap<QString, int> countMap;

    //считаем количество вхождение всех символов из списка разделителей
    //бувка => количество вхождений
    for(int i = 0 ; i < _description.size(); i++)
    {
        const QString charItem = QString(_description[i]);

        if(separatosList.contains(charItem))
        {
            countMap[charItem]++;
        }
    }

    //строим карту количество вхождение => буква
    QMap<int, QString> map2;
    for(const QString &key : countMap.keys())
    {
        map2[countMap[key]] = key;
    }

    QList<int> countList = map2.keys();

    // смотрим ближайшие ключи и ищем пары где
    // количество разделителя ключ-значение на один больше чем
    // количество разделителей между элементами

    for(int i = countList.size() - 1 ; i > 0; i--)
    {
        if(countList[i] - countList[i - 1] == 1)
        {
            ui->keyValueSplitCombo->setCurrentText(map2[countList[i]]);
            ui->listItemSplitCombo->setCurrentText(map2[countList[i - 1]]);
            return true;
        }
    }

    return false;
}

QStringList EnumEditorForm::separators()
{
    return {
            "\\",
            "/",
            "|",
            ".",
            ",",
            ":",
            ";",
            "-"
        };
}

QVariantMap EnumEditorForm::parseText(const QString &_text)
{
    QStringList tokens = _text.split(ui->listItemSplitCombo->currentText());

    QVariantMap out;


    for(const QString &token : tokens)
    {
        QStringList keyValueTokens = token.split(ui->keyValueSplitCombo->currentText());

        if(keyValueTokens.size() < 2)
        {
            continue;
        }

        if(keyValueTokens.size() == 2)
        {
            out[keyValueTokens.first()] = keyValueTokens.last();
        } else
        {
            out[keyValueTokens.first()] = keyValueTokens.mid(1).join("-");
        }
    }

    return out;
}


void EnumEditorForm::loadState(const LayoutSaver &_saver)
{
    _saver.loadGeometry(this, "g");
    _saver.load(ui->variantMapEditor, "variantMapEditor");
    _saver.load(ui->splitter, "splitter1");
    _saver.load(m_savePath, "savePath");
    ui->keyValueSplitCombo->setCurrentText(_saver.value("keyValueComboText").toString());
    ui->listItemSplitCombo->setCurrentText(_saver.value("listItemComboText").toString());
}

void EnumEditorForm::saveState(LayoutSaver &_saver) const
{
    _saver.saveGeometry(this, "g");
    _saver.save(ui->variantMapEditor, "variantMapEditor");
    _saver.save(ui->splitter, "splitter1");
    _saver.save(m_savePath, "savePath");
    _saver.save(ui->keyValueSplitCombo->currentText(), "keyValueComboText");
    _saver.save(ui->listItemSplitCombo->currentText(), "listItemComboText");
}

void EnumEditorForm::initUiComponets()
{
    QStringList comboItems = separators();

    ui->keyValueSplitCombo->addItems(comboItems);
    ui->listItemSplitCombo->addItems(comboItems);
}

void EnumEditorForm::initConnections()
{
}

void EnumEditorForm::on_applyBtn_clicked()
{
    accept();
}

void EnumEditorForm::on_closeBtn_clicked()
{
    reject();
}

void EnumEditorForm::registerCustomTypes()
{
    qRegisterMetaTypeStreamOperators<QMap<QString, QVariantMap>>();
}

void EnumEditorForm::on_parseStringBtn_clicked()
{
    const QString text = ui->plainTextEdit->toPlainText();

    if(text.isEmpty())
    {
        QMessageBox::information(this, tr("Ошибка"), tr("Текст не может быть пустым"));
        return;
    }

    ui->variantMapEditor->setVariantMap(parseText(text));
}


void EnumEditorForm::updateLanguage()
{
    ui->retranslateUi(this);
}

void EnumEditorForm::updateStyle()
{
    ui->parseStringBtn->setIcon(IconsEnum::getIcon(IconsEnum::SP_ArrowUp1));
    ui->detectSeparatorsButton->setIcon(IconsEnum::getIcon(IconsEnum::SP_Radar1));

    ui->applyBtn->setIcon(IconsEnum::getIcon(IconsEnum::SP_Apply2));
    ui->closeBtn->setIcon(IconsEnum::getIcon(QStyle::SP_DialogCloseButton));
}

void EnumEditorForm::on_detectSeparatorsButton_clicked()
{
    if(!detectSeparators(ui->plainTextEdit->toPlainText()))
    {
        QMessageBox::warning(this, tr("Ошибка"), tr("Невозможно определить разделители"));
    } else {
        QMessageBox::information(this, tr("Успешно"), tr("Разделители успешно определены"));
    }
}

}
