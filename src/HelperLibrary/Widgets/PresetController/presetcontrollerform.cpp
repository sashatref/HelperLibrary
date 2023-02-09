#include "presetcontrollerform.h"
#include "ui_presetcontrollerform.h"
#include "Styles/iconsenum.h"

#include "priv/presetcontrollerp.h"

namespace HelperLibraryNS
{

PresetControllerForm::PresetControllerForm(QWidget *parent) :
    ExtendedMainWindow(nullptr),
    p(new PresetControllerP(this)),
    ui(new Ui::PresetControolerForm)
{
    ui->setupUi(this);
    setParent(parent);

    initAll();


    ui->listWidget->installEventFilter(p);
    p->m_searcher->setControlledListWidget(ui->listWidget);
}

PresetControllerForm::~PresetControllerForm()
{
    delete ui;
}

void PresetControllerForm::setPresetFileName(const QString &_fileName)
{
    p->m_presetFileName = _fileName;
}

QString PresetControllerForm::getPresetFileName() const
{
    return p->m_presetFileName;
}

void PresetControllerForm::resetPresetFileName()
{
    setPresetFileName("record-data.rcrd");
}

void PresetControllerForm::setPresetDialogFilter(const QString &_filter)
{
    p->m_presetDialogFilter = _filter;
}

QString PresetControllerForm::getPresetDialogFilter() const
{
    return p->m_presetDialogFilter;
}

void PresetControllerForm::resetPresetDialogFilter()
{
    setPresetDialogFilter("Record-list file(*.rcrd)");
}

QList<QToolBar *> PresetControllerForm::getToolBars()
{
    return {
        ui->toolBar_presetController,
        ui->toolBar_saveLoad,
        ui->toolBar_searchPresets
    };
}

QListWidget *PresetControllerForm::getLW()
{
    return ui->listWidget;
}

bool PresetControllerForm::loadPresetCommand(const QString &_name)
{
    const int count = ui->listWidget->count();

    bool found = false;
    for(int i = 0 ; i < count ; i++)
    {
        QListWidgetItem *lwItem = ui->listWidget->item(i);
        QString name = lwItem->data(presetNameRole).toString();

        if(name == _name)
        {
            lwItem->setSelected(true);
            emit loadPreset(name, lwItem->data(presetDataRole));
            found = true;
        } else
        {
            lwItem->setSelected(false);
        }
    }

    return found;
}

QVariant PresetControllerForm::getPresetData(const QString &_preset)
{
    QListWidgetItem *item = p->findItemWithName(_preset);
    if(item)
    {
        return item->data(presetDataRole);
    }

    return QVariant();
}

void PresetControllerForm::loadState(const LayoutSaver &_saver)
{
    _saver.loadMainWindow(this, "mw");
    _saver.load(p->m_lastPath, "LastPath");
    _saver.load(p->m_searcher, "searcher");

    LayoutSaver presetsSaver;
    presetsSaver.loadFromFile(p->m_presetFileName);
    p->loadPresets(presetsSaver["presets"].toMap());
}

void PresetControllerForm::saveState(LayoutSaver &_saver) const
{
    p->m_searcher->closeSearchForm();

    _saver.saveMainWindow(this, "mw");
    _saver.save(p->m_lastPath, "LastPath");
    _saver.save(p->m_searcher, "searcher");

    LayoutSaver presetsSaver;
    presetsSaver["presets"] = p->savePresets();
    presetsSaver.saveToFile(p->m_presetFileName);
}

void PresetControllerForm::updateLanguage()
{
    ui->retranslateUi(this);
}

void PresetControllerForm::updateStyle()
{
    ui->actionSavePreset->setIcon(IconsEnum::getIcon(IconsEnum::SP_Save1));
    ui->actionRemoveSelected->setIcon(IconsEnum::getIcon(IconsEnum::SP_Minus2));
    ui->actionLoadPreset->setIcon(IconsEnum::getIcon(IconsEnum::SP_Apply2));

    ui->actionLoadFromFile->setIcon(IconsEnum::getIcon(QStyle::SP_DialogOpenButton));
    ui->actionSaveToFile->setIcon(IconsEnum::getIcon(IconsEnum::SP_SaveAs1));
    ui->actionSearch->setIcon(IconsEnum::getIcon(IconsEnum::SP_Search1));
}

void PresetControllerForm::initConnections()
{
    connect(ui->listWidget, &QListWidget::customContextMenuRequested,
            p, &PresetControllerP::presetListContextMenuSlot);

    connect(ui->listWidget, &QListWidget::itemDoubleClicked,
            p, &PresetControllerP::loadPresetSlot);

    connect(ui->actionLoadFromFile, &QAction::triggered, p, &PresetControllerP::loadFromFileSlot);
    connect(ui->actionLoadPreset, &QAction::triggered, p, &PresetControllerP::loadPresetSlot);
    connect(ui->actionRemoveSelected, &QAction::triggered, p, &PresetControllerP::removeSelectedSlot);
    connect(ui->actionSavePreset, &QAction::triggered, p, &PresetControllerP::savePresetSlot);
    connect(ui->actionSaveToFile, &QAction::triggered, p, &PresetControllerP::saveToFileSlot);
    connect(ui->actionSearch, &QAction::triggered, p, &PresetControllerP::showSearchForm);
}



}






