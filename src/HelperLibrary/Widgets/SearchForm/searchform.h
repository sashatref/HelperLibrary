#pragma once

#include <QWidget>

#include "../../export.h"
#include "../extendedwidget.h"

namespace Ui {
class SearchForm;
}

namespace HelperLibraryNS
{

class SearchFormP;

class HELPERLIBRARY_EXPORT SearchForm : public ExtendedWidget
{
    Q_OBJECT
    SearchFormP *p = nullptr;
    friend class SearchFormP;
public:
    explicit SearchForm(QWidget *parent = nullptr);
    ~SearchForm();

    void setCustomWidget(ExtendedWidget *_w);

    bool checkText(const QString &_text);

    template <class Type>
    void setNewSearchPosition(const Type &_value)
    {
        setNewSearchPosition(QVariant::fromValue(_value));
    }
    void setNewSearchPosition(const QVariant &_searchPosition);

public slots:
    void searchFinishedSlot();
    void setSearchPosition(const QString &_text);

signals:
    void resetSearchSignal(SearchForm *_searchForm);
    void searchSignal(SearchForm *_searchForm, const QVariant &_searchPosition);

private:
    Ui::SearchForm *ui;

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
