#pragma once

#include <QDialog>

#include "../extendeddialog.h"

namespace Ui {
class ComplexTextDialog;
}

namespace HelperLibraryNS
{

class ComplexTextEditor;

class HELPERLIBRARY_EXPORT ComplexTextDialog : public ExtendedDialog
{
    Q_OBJECT

public:
    explicit ComplexTextDialog(QWidget *parent = nullptr);
    ~ComplexTextDialog();

    ComplexTextEditor *getEditor();

    void setText(const QString &_text);
    QString getText() const;

private slots:
    void on_applyButton_clicked();
    void on_closeButton_clicked();

private:
    Ui::ComplexTextDialog *ui;

public:
    virtual void loadState(const LayoutSaver &_saver) override;
    virtual void saveState(LayoutSaver &_saver) const override;
    virtual void updateLanguage() override;
    virtual void updateStyle() override;
    virtual void registerCustomTypes() override;

protected:
    virtual void initUiComponets() override;
    virtual void initConnections() override;
};

}
