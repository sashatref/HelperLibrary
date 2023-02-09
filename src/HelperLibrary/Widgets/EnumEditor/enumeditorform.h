#pragma once

#include "../extendeddialog.h"

#include <QMap>
#include <QVariantMap>
#include <QStringList>
#include "../../export.h"

namespace Ui {
class EnumEditorForm;
}

namespace HelperLibraryNS
{

class HELPERLIBRARY_EXPORT EnumEditorForm : public ExtendedDialog
{
    Q_OBJECT

public:
    explicit EnumEditorForm(QWidget *parent = nullptr);
    ~EnumEditorForm();

    void setEnum(const QMap<int, QString> &_enum);
    QMap<int, QString> getEnum() const;

    void setItems(const QList<QPair<int, QString>> &_items);
    QList<QPair<int, QString>> getItems() const;

    void setControlDescription(const QString &_description);

private:
    bool detectSeparators(const QString &_description);

    static QStringList separators();

    Ui::EnumEditorForm *ui;
    QString m_savePath;

    QVariantMap parseText(const QString &_text);

public:
    virtual void loadState(const LayoutSaver &_saver) override;
    virtual void saveState(LayoutSaver &_saver) const override;
    virtual void initUiComponets() override;
    virtual void initConnections() override;
    virtual void registerCustomTypes() override;
    virtual void updateLanguage() override;
    virtual void updateStyle() override;

private slots:
    void on_applyBtn_clicked();
    void on_closeBtn_clicked();
    void on_parseStringBtn_clicked();
    void on_detectSeparatorsButton_clicked();
};

}
