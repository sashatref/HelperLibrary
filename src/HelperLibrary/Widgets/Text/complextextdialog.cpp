#include "complextextdialog.h"
#include "ui_complextextdialog.h"
#include "../../Styles/iconsenum.h"

namespace HelperLibraryNS
{

ComplexTextDialog::ComplexTextDialog(QWidget *parent) :
    ExtendedDialog(parent),
    ui(new Ui::ComplexTextDialog)
{
    ui->setupUi(this);

    initAll();
}

ComplexTextDialog::~ComplexTextDialog()
{
    delete ui;
}

ComplexTextEditor *ComplexTextDialog::getEditor()
{
    return ui->complexTextEditor;
}

void ComplexTextDialog::setText(const QString &_text)
{
    ui->complexTextEditor->setText(_text);
}

QString ComplexTextDialog::getText() const
{
    return ui->complexTextEditor->getText();
}

void ComplexTextDialog::on_applyButton_clicked()
{
    accept();
}

void ComplexTextDialog::on_closeButton_clicked()
{
    reject();
}


void ComplexTextDialog::loadState(const LayoutSaver &_saver)
{
    _saver.loadGeometry(this, "g");
    _saver.load(ui->complexTextEditor, "complexTextEditor");
}

void ComplexTextDialog::saveState(LayoutSaver &_saver) const
{
    _saver.saveGeometry(this, "g");
    _saver.save(ui->complexTextEditor, "complexTextEditor");
}

void ComplexTextDialog::updateLanguage()
{
    ui->retranslateUi(this);
}

void ComplexTextDialog::updateStyle()
{
    ui->applyButton->setIcon(IconsEnum::getIcon(IconsEnum::SP_Apply2));
    ui->closeButton->setIcon(IconsEnum::getIcon(QStyle::SP_DialogCloseButton));
}

void ComplexTextDialog::registerCustomTypes()
{
}

void ComplexTextDialog::initUiComponets()
{
}

void ComplexTextDialog::initConnections()
{
}

}
