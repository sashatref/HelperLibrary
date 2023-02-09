#include "extlist.h"
#include "ui_extlist.h"
#include "../../Styles/iconsenum.h"
#include "../SearchForm/listwidgetsearcher.h"

namespace HelperLibraryNS
{

ExtList::ExtList(QWidget *parent) :
    ExtendedWidget(parent),
    ui(new Ui::ExtList)
{
    ui->setupUi(this);

    initAll();

    m_lwSearcher = new ListWidgetSearcher(this, ui->listWidget);
}

ExtList::~ExtList()
{
    delete ui;
}

void ExtList::setTitle(const QString &_title)
{
    m_lwSearcher->setTitle(_title);
    ui->titleLabel->setText(_title);
}

QString ExtList::getTitle() const
{
    return ui->titleLabel->text();
}

void ExtList::setListWidgetFont(const QFont &_f)
{
    ui->listWidget->setFont(_f);
}

QFont ExtList::getListWidgetFont() const
{
    return ui->listWidget->font();
}

void ExtList::setSelectionMode(QAbstractItemView::SelectionMode _mode)
{
    ui->listWidget->setSelectionMode(_mode);
}

QAbstractItemView::SelectionMode ExtList::getSeletionMode() const
{
    return ui->listWidget->selectionMode();
}

QListWidget *ExtList::lw()
{
    return ui->listWidget;
}

void ExtList::showSearchForm()
{
    m_lwSearcher->createAndShowSearchForm();
}

void ExtList::addToolbarWidget(QWidget *_w, int _index)
{
    QHBoxLayout *lt = qobject_cast<QHBoxLayout*>(ui->frame->layout());

    if(lt)
    {
        lt->insertWidget(_index, _w);
    }
}

void ExtList::setSearchWindowModality(Qt::WindowModality _modality)
{
    m_lwSearcher->setWindowModality(_modality);
}


void ExtList::loadState(const LayoutSaver &_saver)
{
    _saver.load(m_lwSearcher, "searcherState");
}

void ExtList::saveState(LayoutSaver &_saver) const
{
    m_lwSearcher->closeSearchForm();
    _saver.save(m_lwSearcher, "searcherState");
}

void ExtList::updateLanguage()
{
    ui->retranslateUi(this);
}

void ExtList::updateStyle()
{
    ui->sortButton->setIcon(ui->sortButton->isChecked() ?
                                IconsEnum::getIcon(IconsEnum::SP_Desceding1) :
                                IconsEnum::getIcon(IconsEnum::SP_Asceding1));

    ui->searchButton->setIcon(IconsEnum::getIcon(IconsEnum::SP_Search1));
}

void ExtList::registerCustomTypes()
{
}

void ExtList::initUiComponets()
{
}

void ExtList::initConnections()
{
}

void ExtList::on_sortButton_toggled(bool checked)
{
    ui->sortButton->setIcon(checked ?
                                IconsEnum::getIcon(IconsEnum::SP_Desceding1) :
                                IconsEnum::getIcon(IconsEnum::SP_Asceding1));

    ui->listWidget->sortItems(checked ? Qt::DescendingOrder : Qt::AscendingOrder);
}

void ExtList::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_F && event->modifiers().testFlag(Qt::ControlModifier))
    {
        showSearchForm();
    }

    if(event->key() == Qt::Key_Delete)
    {
        emit deletePressed(ui->listWidget->selectedItems());
    }

    return ExtendedWidget::keyReleaseEvent(event);
}

void ExtList::on_searchButton_clicked()
{
    showSearchForm();
}

}




