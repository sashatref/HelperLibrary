#include "filterwidget.h"
#include "ui_filterwidget.h"
#include "../../Styles/iconsenum.h"
#include "priv/filterwidgetconfigdialog.h"
#include "priv/filterwidgetconf.h"

namespace HelperLibraryNS
{

FilterWidget::FilterWidget(QWidget *parent) :
    ExtendedWidget  (parent),
    ui              (new Ui::FilterWidget),
    p               (new FilterWidgetConf())
{
    ui->setupUi(this);

    initAll();

    updatePlaceholderText();
}

FilterWidget::~FilterWidget()
{
    delete ui;
}

bool FilterWidget::checkText(const QString &_text)
{
    const QString searchtext = ui->searchCombo->currentText();

    if(searchtext.isEmpty())
    {
        return true;
    }



    if(p->pattern == QRegExp::FixedString)
    {
        return _text.contains(searchtext, p->caseSensitivity);
    }

    QRegExp rx(searchtext);
    rx.setPatternSyntax(p->pattern);
    rx.setCaseSensitivity(p->caseSensitivity);
    return rx.exactMatch(_text);
}

bool FilterWidget::isEmptyInput() const
{
    return ui->searchCombo->currentText().isEmpty();
}

void FilterWidget::on_filterButton_clicked()
{
    emit startFilter();

    applySearchItem(ui->searchCombo->currentText());
}

void FilterWidget::on_configButton_clicked()
{
    FilterWidgetConfigDialog dialog(this);
    dialog.setConfig(*p);

    connect(&dialog, &FilterWidgetConfigDialog::clearHistory, this, [=]
    {
        if(QMessageBox::No == QMessageBox::question(this, tr("Очистить?"), tr("Очистить историю поиска?")))
        {
            return;
        }

        ui->searchCombo->clear();
    });

    if(dialog.exec() == QDialog::Accepted)
    {
        *p = dialog.getConfig();

        updatePlaceholderText();
    }
}


void FilterWidget::updatePlaceholderText()
{
    ui->searchCombo->lineEdit()->setPlaceholderText(tr("Введите текст фильтра (%1)")
                                                    .arg(p->patternToString()));
}

void FilterWidget::applySearchItem(const QString &_text)
{
    if(_text.isEmpty())
    {
        return;
    }

    QSignalBlocker blocker(ui->searchCombo->lineEdit());

    for(int i = ui->searchCombo->count() - 1 ; i > -1; i--)
    {
        if(ui->searchCombo->itemText(i) == _text)
        {
            ui->searchCombo->removeItem(i);
        }
    }

    ui->searchCombo->insertItem(0, _text);
    ui->searchCombo->setCurrentIndex(0);
}

void FilterWidget::loadState(const LayoutSaver &_saver)
{
    QSignalBlocker blocker(ui->searchCombo->lineEdit());
    _saver.load(ui->searchCombo, "searchCombo");
    p->load(_saver["config"]);

    updatePlaceholderText();
}

void FilterWidget::saveState(LayoutSaver &_saver) const
{
    _saver.save(ui->searchCombo, "searchCombo");
    _saver["config"] = p->save();
}

void FilterWidget::updateLanguage()
{
    ui->retranslateUi(this);

    updatePlaceholderText();
}

void FilterWidget::updateStyle()
{
    ui->filterButton->setIcon(IconsEnum::getIcon(IconsEnum::SP_Filter2));
    ui->configButton->setIcon(IconsEnum::getIcon(IconsEnum::SP_Setting2));
}

void FilterWidget::initUiComponets()
{
    ui->searchCombo->setAutoCompletionCaseSensitivity(Qt::CaseSensitive);
    ui->searchCombo->lineEdit()->setClearButtonEnabled(true);
}


void FilterWidget::initConnections()
{
    connect(ui->searchCombo->lineEdit(), &QLineEdit::returnPressed, this, [=]
    {
        if(m_checkOnlyOnEnter)
        {
            on_filterButton_clicked();
        }
    });
    connect(ui->searchCombo->lineEdit(), &QLineEdit::textChanged, this, [=]
    {
        if(!m_checkOnlyOnEnter)
        {
            on_filterButton_clicked();
        }
    });
}


}
