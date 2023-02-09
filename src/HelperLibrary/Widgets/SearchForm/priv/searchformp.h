#pragma once

#include "../searchform.h"
#include "ui_searchform.h"

namespace HelperLibraryNS
{

class SearchFormP : public QObject
{
    Q_OBJECT
public:
    SearchForm *q;

    SearchFormP(SearchForm *_q);

    void search();
    void resetSearch();

    Qt::CaseSensitivity getCaseSensitivity() const;

    bool checkDefault(const QString &_sourceText, const QString &_textToSearch);
    bool checkWildCard(const QString &_sourceText, const QString &_textToSearch);
    bool checkRegExp(const QString &_sourceText, const QString &_textToSearch);

    QVariant saveRBState() const;
    void loadRBState(const QVariant &_v);

    QString getCheckedRb() const;

    QVariant saveHistory() const;
    void loadHistory(const QVariant &_v);

    QMap<QString, std::function<bool(const QString &, const QString &)>> m_factory;

    QVariant m_searchPosition;
    ExtendedWidget *m_extraConfigForm = nullptr;

public slots:
    void onCancelButtonClicked();
    void onSearchNextButton_clicked();
    void onNewSearchButton_clicked();
    void onOpacitySlider_valueChanged(int value);
    void onClearHistorybtn_clicked();
    void searchTextComboEnterPressed();
    void extConfigBtnClicked(bool _checked);
};

}

