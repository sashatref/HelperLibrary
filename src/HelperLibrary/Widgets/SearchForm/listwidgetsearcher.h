#pragma once

#include <QObject>
#include <QPointer>

#include "../isavewidget.h"
#include "../layoutsaver.h"
#include "searchform.h"

class QListWidget;

namespace HelperLibraryNS
{

class ListWidgetSearcher : public QObject, public ISaveWidget
{
    Q_OBJECT
    QListWidget *m_lw = nullptr;
    QString m_title;
    Qt::WindowModality m_modality = Qt::NonModal;
public:
    struct SearchPosInfo
    {
        int listIndex = -1;
    };

    void setWindowModality(Qt::WindowModality _modality);

    ListWidgetSearcher(QObject *_parent, QListWidget * _lw);
    void setTitle(const QString &_title);
    void setControlledListWidget(QListWidget *_lw);

    void createAndShowSearchForm();
    void closeSearchForm();

    virtual QString getItemText(QListWidgetItem *_item);

private slots:
    void searchNext(SearchForm *_searchForm, const QVariant &_searchPos);
    void resetSearchInfo(SearchForm *_searchForm);

private:
    QVariant m_searchFormState;
    QPointer<SearchForm> m_searchForm;

    void updateTitle();

    // ISaveWidget interface
public:
    virtual QString getWidgetUniqueName() const override;
    virtual void loadState(const LayoutSaver &_saver) override;
    virtual void saveState(LayoutSaver &_saver) const override;
};

}

Q_DECLARE_METATYPE(HelperLibraryNS::ListWidgetSearcher::SearchPosInfo)

