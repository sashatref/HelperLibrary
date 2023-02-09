#pragma once

#include <QWidget>

#include "../extendedwidget.h"

namespace Ui {
class FilterWidget;
}


namespace HelperLibraryNS
{

class FilterWidgetConf;
class HELPERLIBRARY_EXPORT FilterWidget : public ExtendedWidget
{
    Q_OBJECT
    QScopedPointer<FilterWidgetConf> p;
    Q_PROPERTY(bool checkOnlyOnEnter MEMBER m_checkOnlyOnEnter)
public:
    explicit FilterWidget(QWidget *parent = nullptr);
    ~FilterWidget();

    bool checkText(const QString &_text);

    bool isEmptyInput() const;

signals:
    void startFilter();

private slots:
    void on_filterButton_clicked();
    void on_configButton_clicked();

private:
    Ui::FilterWidget *ui;
    bool m_checkOnlyOnEnter = true;

    void updatePlaceholderText();
    void applySearchItem(const QString &_text);

public:
    virtual void loadState(const LayoutSaver &_saver) override;
    virtual void saveState(LayoutSaver &_saver) const override;
    virtual void updateLanguage() override;
    virtual void updateStyle() override;
    virtual void initUiComponets() override;
    virtual void initConnections() override;
};

}

