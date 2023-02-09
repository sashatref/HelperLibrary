#pragma once
#include <QMainWindow>

#include "../../export.h"
#include "../extendedmainwindow.h"

namespace Ui {
class PresetControolerForm;
}


/*
 * Подключаем как минимум 2 слота:
 * loadPreset(const QString &_name, const QVariant &_data) - где _data это наши данные из пресета
 * savePreset(const QString &_name, QVariant &_data, bool &_isOk) - где в _data записываем наши данные пресета
 * если что-то пошло не так, то в _isOk записываем false
 */

namespace HelperLibraryNS
{

class PresetControllerP;
class HELPERLIBRARY_EXPORT PresetControllerForm : public ExtendedMainWindow
{
    Q_OBJECT
    PresetControllerP *p;
    friend class PresetControllerP;

    Q_PROPERTY(QString presetFileName READ getPresetFileName WRITE setPresetFileName RESET resetPresetFileName)
    Q_PROPERTY(QString presetDialogFilter READ getPresetDialogFilter WRITE setPresetDialogFilter RESET resetPresetDialogFilter)
public:
    explicit PresetControllerForm(QWidget *parent = nullptr);
    ~PresetControllerForm() override;

    void setPresetFileName(const QString &_fileName);
    QString getPresetFileName() const;
    void resetPresetFileName();

    void setPresetDialogFilter(const QString &_filter);
    QString getPresetDialogFilter() const;
    void resetPresetDialogFilter();

    QList<QToolBar*> getToolBars();

    QListWidget *getLW();

    bool loadPresetCommand(const QString &_name);

    QVariant getPresetData(const QString &_preset);

signals:
    void previewPreset(const QString &_name, const QVariant &_data);
    void loadPreset(const QString &_name, const QVariant &_data);
    void savePreset(const QString &_name, QVariant &_data, bool &_isOk);
    void removePreset(const QString &_name, const QVariant &_data);
    void presetListUpdated(const QVariantMap &_presets);

private:
    Ui::PresetControolerForm *ui;

public:
    virtual void loadState(const LayoutSaver &_saver) override;
    virtual void saveState(LayoutSaver &_saver) const override;
    virtual void updateLanguage() override;
    virtual void updateStyle() override;
    virtual void initConnections() override;
};

}

