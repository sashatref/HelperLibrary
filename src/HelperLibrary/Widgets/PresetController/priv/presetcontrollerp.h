#pragma once

#include "../presetcontrollerform.h"
#include "Widgets/SearchForm/listwidgetsearcher.h"

namespace HelperLibraryNS
{

enum
{
    presetDataRole = Qt::UserRole,
    presetNameRole
};

class PresetControllerP : public QObject
{
    Q_OBJECT
    PresetControllerForm *q;
public:
    PresetControllerP(PresetControllerForm *_q);

public slots:
    void presetListContextMenuSlot(const QPoint &_pos);

    void savePresetSlot();
    void loadPresetSlot();
    void removeSelectedSlot();
    void loadFromFileSlot();
    void saveToFileSlot();
    void showSearchForm();

public:
    void loadPresets(const QVariantMap &_presets);
    void addPresets(const QVariantMap &_presets);
    QVariantMap savePresets() const;

    QVariantMap saveSelectedPresets() const;

    void addListItem(const QString &_preset, const QVariant &_value);
    void updateListItem(QListWidgetItem *_item, const QVariant &_value, const QString &_newPresetName);
    QListWidgetItem *findItemWithName(const QString &_name);

    QListWidgetItem *getSelectedItem();

    ListWidgetSearcher *m_searcher = nullptr;

    QString m_lastPath;
    QString m_presetDialogFilter = "Record-list file(*.rcrd)";
    QString m_presetFileName = "record-data.rcrd";

    // QObject interface
public:
    virtual bool eventFilter(QObject *watched, QEvent *event) override;
};

}
