#pragma once

#include <QWidget>

#include "../extendedwidget.h"
#include "../../export.h"


namespace Ui {
class ExtList;
}

namespace HelperLibraryNS
{

class ListWidgetSearcher;

class HELPERLIBRARY_EXPORT ExtList : public ExtendedWidget
{
    Q_OBJECT
    Q_PROPERTY(QString title READ getTitle WRITE setTitle)
    Q_PROPERTY(QFont listWidgetFont READ getListWidgetFont WRITE setListWidgetFont)
    Q_PROPERTY(QAbstractItemView::SelectionMode listSelectionMode READ getSeletionMode WRITE setSelectionMode)
public:
    Q_ENUM(QAbstractItemView::SelectionMode)

    explicit ExtList(QWidget *parent = nullptr);
    ~ExtList();

    void setTitle(const QString &_title);
    QString getTitle() const;

    void setListWidgetFont(const QFont &_f);
    QFont getListWidgetFont() const;

    void setSelectionMode(QAbstractItemView::SelectionMode _mode);
    QAbstractItemView::SelectionMode getSeletionMode() const;

    QListWidget *lw();

    void addToolbarWidget(QWidget *_w, int _index);

    void setSearchWindowModality(Qt::WindowModality _modality);

signals:
    void deletePressed(const QList<QListWidgetItem*> &_selected);

private:
    Ui::ExtList *ui;
    ListWidgetSearcher *m_lwSearcher = nullptr;

    void showSearchForm();

    // ISaveWidget interface
public:
    virtual void loadState(const LayoutSaver &_saver) override;
    virtual void saveState(LayoutSaver &_saver) const override;

    // ExtendedWidget interface
public:
    virtual void updateLanguage() override;
    virtual void updateStyle() override;
    virtual void registerCustomTypes() override;

protected:
    virtual void initUiComponets() override;
    virtual void initConnections() override;
    virtual void keyPressEvent(QKeyEvent *event) override;

private slots:
    void on_sortButton_toggled(bool checked);
    void on_searchButton_clicked();
};

}
