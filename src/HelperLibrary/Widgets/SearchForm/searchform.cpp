#include "searchform.h"
#include "ui_searchform.h"
#include "Styles/iconsenum.h"
#include "priv/searchformp.h"

namespace HelperLibraryNS
{

SearchForm::SearchForm(QWidget *parent) :
    ExtendedWidget  (parent),
    p               (new SearchFormP(this)),
    ui              (new Ui::SearchForm)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Window
                   | Qt::WindowCloseButtonHint
                   | Qt::WindowContextHelpButtonHint
                   | Qt::WindowStaysOnTopHint);
    setFixedSize(size());

    using namespace std::placeholders;
    p->m_factory[ui->defaultRB->objectName()] = std::bind(&SearchFormP::checkDefault, p, _1, _2);
    p->m_factory[ui->wildCardRB->objectName()] = std::bind(&SearchFormP::checkWildCard, p, _1, _2);
    p->m_factory[ui->regExpRB->objectName()] = std::bind(&SearchFormP::checkRegExp, p, _1, _2);

    initAll();
}

SearchForm::~SearchForm()
{
    if(p->m_extraConfigForm)
    {
        delete p->m_extraConfigForm;
    }

    delete p;
    delete ui;
}

void SearchForm::setCustomWidget(ExtendedWidget *_w)
{
    p->m_extraConfigForm = _w;
    ui->extConfigButton->setVisible(_w);

    if(_w)
    {
        _w->setWindowTitle(tr("Дополнительные настройки"));
        _w->setWindowFlags(Qt::Tool | Qt::WindowSystemMenuHint | Qt::WindowStaysOnTopHint);
    }
}

bool SearchForm::checkText(const QString &_text)
{
    const QString rbObjName = p->getCheckedRb();
    auto it = p->m_factory.find(rbObjName);
    if(it == p->m_factory.end())
    {
        QMessageBox::warning(this, tr("Ошибка"), tr("Выберите режим поиска"));
        return false;
    }

    return it.value()(_text, ui->searchTextCombo->currentText());
}

void SearchForm::setNewSearchPosition(const QVariant &_searchPosition)
{
    p->m_searchPosition = _searchPosition;
}


void SearchForm::searchFinishedSlot()
{
    QMessageBox::information(this, tr("Завершено!"), tr("Поиск завершен"));
}

void SearchForm::setSearchPosition(const QString &_text)
{
    ui->positionLineEdit->setText(_text);
}

void SearchForm::loadState(const LayoutSaver &_saver)
{
    _saver.loadGeometry(this, "g");
    p->loadRBState(_saver.value("rbState", "defaultRB"));
    _saver.load(ui->registryCheckBox, "registryCheckBox");
    ui->opacitySlider->setValue(_saver.value("opacity", 100).toInt());
    p->loadHistory(_saver.value("history"));

    if(p->m_extraConfigForm)
    {
        bool isVisible = _saver["extraConfigFormVisible"].toBool();

        if(isVisible)
        {
            QSignalBlocker blocker(ui->extConfigButton);
            ui->extConfigButton->setChecked(isVisible);
            p->extConfigBtnClicked(isVisible);
        }

        _saver.load(p->m_extraConfigForm, "extraConfigForm");
    }
}

void SearchForm::saveState(LayoutSaver &_saver) const
{
    _saver.saveGeometry(this, "g");
    _saver["rbState"] = p->saveRBState();
    _saver.save(ui->registryCheckBox, "registryCheckBox");
    _saver.save(ui->opacitySlider->value(), "opacity");
    _saver["history"] = p->saveHistory();

    if(p->m_extraConfigForm)
    {
        _saver.save(p->m_extraConfigForm->isVisible(), "extraConfigFormVisible");
        _saver.save(p->m_extraConfigForm, "extraConfigForm");
    }
}

void SearchForm::updateLanguage()
{
    ui->retranslateUi(this);
}

void SearchForm::updateStyle()
{
    ui->clearHistorybtn->setIcon(IconsEnum::getIcon(QStyle::SP_DialogCloseButton));
}

void SearchForm::initUiComponets()
{
    ui->searchTextCombo->lineEdit()->setPlaceholderText(tr("Что искать?"));
    ui->searchTextCombo->setAutoCompletionCaseSensitivity(Qt::CaseSensitive);
    ui->extConfigButton->setVisible(false);
}

void SearchForm::initConnections()
{
    connect(ui->searchTextCombo->lineEdit(), &QLineEdit::returnPressed, p, &SearchFormP::searchTextComboEnterPressed);
    connect(ui->cancelButtn, &QPushButton::clicked, p, &SearchFormP::onCancelButtonClicked);
    connect(ui->opacitySlider, &QSlider::valueChanged, p, &SearchFormP::onOpacitySlider_valueChanged);
    connect(ui->clearHistorybtn, &QToolButton::clicked, p, &SearchFormP::onClearHistorybtn_clicked);
    connect(ui->newSearchButton, &QPushButton::clicked, p, &SearchFormP::onNewSearchButton_clicked);
    connect(ui->searchNextButton, &QPushButton::clicked, p, &SearchFormP::onSearchNextButton_clicked);
    connect(ui->extConfigButton, &QPushButton::clicked, p, &SearchFormP::extConfigBtnClicked);
}


}


