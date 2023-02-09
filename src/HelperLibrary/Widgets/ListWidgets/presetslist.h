#pragma once

#include <QWidget>
#include "../../export.h"
#include "../extendedwidget.h"

namespace Ui {
class PresetsList;
}

namespace HelperLibraryNS
{

class HELPERLIBRARY_EXPORT PresetsList : public ExtendedWidget
{
    Q_OBJECT
    Q_PROPERTY(int loadPresetsBtnVisible READ getLoadBtnVisible WRITE setLoadBtnVisible)
public:
    explicit PresetsList(QWidget *parent = nullptr);
    ~PresetsList();

    void setLoadBtnVisible(bool _isVisible);
    int getLoadBtnVisible() const;

    void loadPresets(const QStringList &_presets);
    QStringList savePresets() const;

    QString getSelectedPreset() const;

signals:
    void previewPreset(const QString &_presetName);
    void loadPreset(const QString &_preset);
    void savePreset(const QString &_preset);
    void removePreset(const QString &_preset);
    void renamePreset(const QString &_oldName, const QString &_newName);

private slots:
    void on_saveBtn_clicked();
    void on_removeBtn_clicked();
    void on_loadBtn_clicked();

    void currentItemChangedSlot(QListWidgetItem *_current, QListWidgetItem *_prev);

private:
    Ui::PresetsList *ui;

    QListWidgetItem *getSelectedItem();

    // ExtendedWidget interface
public:
    virtual void updateLanguage() override;
    virtual void updateStyle() override;

protected:
    virtual void initUiComponets() override;
    virtual void initConnections() override;
};

}
