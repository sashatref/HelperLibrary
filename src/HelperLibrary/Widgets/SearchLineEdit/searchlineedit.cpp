#include "searchlineedit.h"
#include "ui_searchlineedit.h"
#include "Styles/iconsenum.h"

namespace HelperLibraryNS
{

class SearchLineEditP
{
    SearchLineEdit *q;
public:
    SearchLineEditP(SearchLineEdit *_q): q(_q) {}

    QVariant saveHistory() const
    {
        QStringList out;

        for(int i = 0 ; i < q->ui->searchTextCombo->count(); i++)
        {
            out << q->ui->searchTextCombo->itemText(i);
        }

        return out;
    }

    void loadHistory(const QVariant &_v)
    {
        const QStringList items = _v.toStringList();
        for(auto &item : items)
        {
            q->ui->searchTextCombo->addItem(item);
        }
    }
};

SearchLineEdit::SearchLineEdit(QWidget *parent) :
    ExtendedWidget(parent),
    ui(new Ui::SearchLineEdit),
    p(new SearchLineEditP(this))
{
    ui->setupUi(this);
}

SearchLineEdit::~SearchLineEdit()
{
    delete p;
    delete ui;
}

void SearchLineEdit::loadState(const LayoutSaver &_saver)
{
    p->loadHistory(_saver.value("history"));
}

void SearchLineEdit::saveState(LayoutSaver &_saver) const
{
    _saver.save(p->saveHistory(), "history");
}

void SearchLineEdit::updateLanguage()
{
    ui->retranslateUi(this);
}

void SearchLineEdit::updateStyle()
{
    ui->clearHistoryBtn->setIcon(IconsEnum::getIcon(QStyle::SP_DialogCloseButton));
}

void SearchLineEdit::initUiComponets()
{
    ui->searchTextCombo->lineEdit()->setPlaceholderText(tr("Что искать?"));
}

void SearchLineEdit::initConnections()
{

}

}


