#pragma once

#include <QWidget>
#include "../../export.h"
#include "../extendedwidget.h"

namespace Ui {
class SearchLineEdit;
}

namespace HelperLibraryNS
{

class SearchLineEditP;
class HELPERLIBRARY_EXPORT SearchLineEdit : public ExtendedWidget
{
    Q_OBJECT
    SearchLineEditP *p;
    friend class SearchLineEditP;
public:
    explicit SearchLineEdit(QWidget *parent = nullptr);
    ~SearchLineEdit();

private:
    Ui::SearchLineEdit *ui;

    // ISaveWidget interface
public:
    virtual void loadState(const LayoutSaver &_saver) override;
    virtual void saveState(LayoutSaver &_saver) const override;
    virtual void updateLanguage() override;
    virtual void updateStyle() override;
    virtual void initUiComponets() override;
    virtual void initConnections() override;
};

}
