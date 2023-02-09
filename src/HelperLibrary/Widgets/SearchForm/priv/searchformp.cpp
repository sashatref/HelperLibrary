#include "searchformp.h"

namespace HelperLibraryNS
{

SearchFormP::SearchFormP(SearchForm *_q):
    q(_q)
{

}

void SearchFormP::search()
{
    const QString searchText = q->ui->searchTextCombo->currentText();

    if(searchText.isEmpty())
    {
        QMessageBox::warning(q, tr("Пусто"), tr("Текст для поиска не может быть пустым"));
        return;
    }

    for(int i = q->ui->searchTextCombo->count() - 1 ; i > -1; i--)
    {
        if(q->ui->searchTextCombo->itemText(i) == searchText)
        {
            q->ui->searchTextCombo->removeItem(i);
        }
    }

    q->ui->searchTextCombo->insertItem(0, searchText);
    q->ui->searchTextCombo->setCurrentIndex(0);

    emit q->searchSignal(q, m_searchPosition);
}

void SearchFormP::resetSearch()
{
    emit q->resetSearchSignal(q);
}

Qt::CaseSensitivity SearchFormP::getCaseSensitivity() const
{
    return q->ui->registryCheckBox->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive;
}

bool SearchFormP::checkDefault(const QString &_sourceText, const QString &_textToSearch)
{
    return _sourceText.contains(_textToSearch, getCaseSensitivity());
}

bool SearchFormP::checkWildCard(const QString &_sourceText, const QString &_textToSearch)
{
    QRegExp rx(_textToSearch);
    rx.setPatternSyntax(QRegExp::Wildcard);
    rx.setCaseSensitivity(getCaseSensitivity());
    return rx.exactMatch(_sourceText);
}

bool SearchFormP::checkRegExp(const QString &_sourceText, const QString &_textToSearch)
{
    QRegExp rx(_textToSearch);
    rx.setCaseSensitivity(getCaseSensitivity());
    return rx.exactMatch(_sourceText);
}

QVariant SearchFormP::saveRBState() const
{
    QList<QRadioButton*> rbList = {
        q->ui->defaultRB,
        q->ui->regExpRB,
        q->ui->wildCardRB
    };

    for(auto *item : rbList)
    {
        if(item->isChecked())
        {
            return item->objectName();
        }
    }

    return QString();
}

void SearchFormP::loadRBState(const QVariant &_v)
{
    const QString checkedObjectName = _v.toString();

    QList<QRadioButton*> rbList = {
        q->ui->defaultRB,
        q->ui->regExpRB,
        q->ui->wildCardRB
    };

    for(auto *item : rbList)
    {
        if(item->objectName() == checkedObjectName)
        {
            item->setChecked(true);
            return;
        }
    }
}

QString SearchFormP::getCheckedRb() const
{
    QList<QRadioButton*> rbList = {
        q->ui->defaultRB,
        q->ui->regExpRB,
        q->ui->wildCardRB
    };

    for(auto *item : rbList)
    {
        if(item->isChecked())
        {
            return item->objectName();
        }
    }

    return QString();
}

QVariant SearchFormP::saveHistory() const
{
    QStringList out;

    for(int i = 0 ; i < q->ui->searchTextCombo->count(); i++)
    {
        out << q->ui->searchTextCombo->itemText(i);
    }

    return out;
}

void SearchFormP::loadHistory(const QVariant &_v)
{
    const QStringList items = _v.toStringList();
    for(auto &item : items)
    {
        q->ui->searchTextCombo->addItem(item);
    }

    q->ui->searchTextCombo->lineEdit()->selectAll();
}

void SearchFormP::onCancelButtonClicked()
{
    q->close();
}

void SearchFormP::onSearchNextButton_clicked()
{
    search();
}

void SearchFormP::onNewSearchButton_clicked()
{
    q->ui->searchNextButton->setEnabled(true);
    q->ui->newSearchButton->setDefault(false);

    resetSearch();
    search();
}

void SearchFormP::onOpacitySlider_valueChanged(int value)
{
    q->setWindowOpacity(value / 100.f);
}

void SearchFormP::onClearHistorybtn_clicked()
{
    if(QMessageBox::No == QMessageBox::question(q, tr("Очистить?"), tr("Очистить историю поиска?")))
    {
        return;
    }

    q->ui->searchTextCombo->clear();
}

void SearchFormP::searchTextComboEnterPressed()
{
    if(q->ui->searchNextButton->isEnabled())
    {
        onSearchNextButton_clicked();
    } else
    {
        onNewSearchButton_clicked();
    }
}

void SearchFormP::extConfigBtnClicked(bool _checked)
{
    if(m_extraConfigForm)
    {
        m_extraConfigForm->setVisible(_checked);
    }
}

}
