#include "listwidgetsearcher.h"
#include "releaseassert.h"

namespace HelperLibraryNS
{

void ListWidgetSearcher::setWindowModality(Qt::WindowModality _modality)
{
    m_modality = _modality;
}

ListWidgetSearcher::ListWidgetSearcher(QObject *_parent, QListWidget * _lw):
    QObject(_parent),
    m_lw(_lw)
{

}

void ListWidgetSearcher::setTitle(const QString &_title)
{
    m_title = _title;
    updateTitle();
}


void ListWidgetSearcher::updateTitle()
{
    if(m_searchForm)
    {
        QString text = tr("Поиск");
        if(!m_title.isEmpty())
        {
            text += " - " + m_title;
        }

        m_searchForm->setWindowTitle(text);
    }
}

void ListWidgetSearcher::setControlledListWidget(QListWidget *_lw)
{
    m_lw = _lw;
}

void ListWidgetSearcher::createAndShowSearchForm()
{
    if(!m_searchForm)
    {
        m_searchForm = new SearchForm();
        m_searchForm->setWindowModality(m_modality);
        m_searchForm->setAttribute(Qt::WA_DeleteOnClose);
        m_searchForm->loadWidgetState(m_searchFormState);
        connect(m_searchForm, &SearchForm::resetSearchSignal, this, &ListWidgetSearcher::resetSearchInfo);
        connect(m_searchForm, &SearchForm::searchSignal, this, &ListWidgetSearcher::searchNext);

        m_searchForm->setOnSaveCallback([this](const QVariant &_state)
        {
            m_searchFormState = _state;
        });
        updateTitle();
        m_searchForm->show();
    } else
    {
#ifdef Q_OS_WIN
        SetForegroundWindow((HWND)m_searchForm->winId());
#endif
    }
}

void ListWidgetSearcher::closeSearchForm()
{
    if(m_searchForm)
    {
        m_searchForm->close();
    }
}

QString ListWidgetSearcher::getItemText(QListWidgetItem *_item)
{
    return _item->text();
}

void ListWidgetSearcher::searchNext(SearchForm *_searchForm, const QVariant &_searchPos)
{
    R_ASSERT(m_lw)

    SearchPosInfo searchPos = _searchPos.value<SearchPosInfo>();

    searchPos.listIndex++;

    for( ; searchPos.listIndex < m_lw->count(); searchPos.listIndex++)
    {
        _searchForm->setSearchPosition(QString("%1/%2")
                                       .arg(searchPos.listIndex + 1)
                                       .arg(m_lw->count()));

        QListWidgetItem *item = m_lw->item(searchPos.listIndex);

        if(_searchForm->checkText(getItemText(item)))
        {
            m_lw->clearSelection();
            item->setSelected(true);
            _searchForm->setNewSearchPosition(searchPos);
            m_lw->scrollToItem(item);
            return;
        }
    }

    _searchForm->searchFinishedSlot();
}

void ListWidgetSearcher::resetSearchInfo(SearchForm *_searchForm)
{
    _searchForm->setNewSearchPosition(SearchPosInfo{});
}


QString ListWidgetSearcher::getWidgetUniqueName() const
{
    return objectName();
}

void ListWidgetSearcher::loadState(const LayoutSaver &_saver)
{
    _saver.load(m_searchFormState, "searchFormState");
}

void ListWidgetSearcher::saveState(LayoutSaver &_saver) const
{
    _saver.save(m_searchFormState, "searchFormState");
}

}


