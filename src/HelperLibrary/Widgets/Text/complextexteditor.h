#pragma once

#include <QWidget>

#include "../extendedmainwindow.h"
#include "../../export.h"
#include "../../objectfactory.h"


namespace Ui {
class ComplexTextEditor;
}

namespace HelperLibraryNS
{

class ComplexTextEditorP;

class HELPERLIBRARY_EXPORT ComplexTextEditor : public ExtendedMainWindow
{
    Q_OBJECT
public:
    explicit ComplexTextEditor(QWidget *parent = nullptr);
    ~ComplexTextEditor();

    void setText(const QString &_text);
    QString getText() const;

private:
    friend class ComplexTextEditorP;
    Ui::ComplexTextEditor *ui;
    ComplexTextEditorP *p;

public:
    virtual void loadState(const LayoutSaver &_saver) override;
    virtual void saveState(LayoutSaver &_saver) const override;
    virtual void updateLanguage() override;
    virtual void updateStyle() override;
    virtual void registerCustomTypes() override;

protected:
    virtual void initUiComponets() override;
    virtual void initConnections() override;
private slots:
    void on_actionFormatText_triggered();
};

}
