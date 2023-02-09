#include "complextexteditor.h"
#include "ui_complextexteditor.h"
#include "../../Styles/iconsenum.h"
#include "priv/complextexteditorp.h"

#include <QClipboard>

namespace HelperLibraryNS
{

ComplexTextEditor::ComplexTextEditor(QWidget *parent) :
    ExtendedMainWindow(),
    ui(new Ui::ComplexTextEditor),
    p(new ComplexTextEditorP(this))
{
    ui->setupUi(this);

    setParent(parent);

    initAll();
}

ComplexTextEditor::~ComplexTextEditor()
{
    delete p;
    delete ui;
}

void ComplexTextEditor::setText(const QString &_text)
{
    ui->textEdit->setPlainText(_text);
}

QString ComplexTextEditor::getText() const
{
    return ui->textEdit->toPlainText();
}



void ComplexTextEditor::loadState(const LayoutSaver &_saver)
{
    _saver.load(p->m_lastPath, "lastPath");
    _saver.load(p->m_lastHighlighterName, "hlName");

    ui->fontSizeCombo->setCurrentText(_saver["fontSize"].toString());

    p->useType(p->m_lastHighlighterName);
    p->setActionChecked(p->m_lastHighlighterName);
}

void ComplexTextEditor::saveState(LayoutSaver &_saver) const
{
    _saver.save(p->m_lastPath, "lastPath");
    _saver.save(p->m_lastHighlighterName, "hlName");
    _saver.save(ui->fontSizeCombo->currentText(), "fontSize");
}

void ComplexTextEditor::updateLanguage()
{
    ui->retranslateUi(this);
}

void ComplexTextEditor::updateStyle()
{
    ui->actionLoadFromFile->setIcon(IconsEnum::getIcon(QStyle::SP_DialogOpenButton));
    ui->actionSaveToFile->setIcon(IconsEnum::getIcon(IconsEnum::SP_Save1));

    ui->actionCopy->setIcon(IconsEnum::getIcon(IconsEnum::SP_Copy1));
    ui->actionCut->setIcon(IconsEnum::getIcon(IconsEnum::SP_Cut1));
    ui->actionPaste->setIcon(IconsEnum::getIcon(IconsEnum::SP_Paste2));

    ui->actionUndo->setIcon(IconsEnum::getIcon(IconsEnum::SP_Undo1));
    ui->actionRedo->setIcon(IconsEnum::getIcon(IconsEnum::SP_Redo1));

    ui->actionNew->setIcon(IconsEnum::getIcon(IconsEnum::SP_NewDocument2));

    ui->actionFormatText->setIcon(IconsEnum::getIcon(IconsEnum::SP_TextWidth1));
}

void ComplexTextEditor::registerCustomTypes()
{

}

void ComplexTextEditor::initUiComponets()
{
    QFont f = ui->textEdit->font();
    f.setStyleHint(QFont::Monospace);
    f.setFixedPitch(true);
    ui->textEdit->setFont(f);

    {   //устанавливаем ширину табов
        const int tabStop = 4;  // 4 characters
        QFontMetrics metrics(f);
        ui->textEdit->setTabStopWidth(tabStop * metrics.width(' '));
    }

    p->registerFactoryFunc();
    p->createActions();

    ui->fontSizeCombo->addItems({
                                    "6", "7", "8", "9", "10", "11", "12",
                                    "14", "16", "20", "24", "36", "72"
                                });

    p->clipboardDataChangedSlot();
}

void ComplexTextEditor::initConnections()
{
    connect(ui->actionSaveToFile, &QAction::triggered, p, &ComplexTextEditorP::saveBtnClickedSlot);
    connect(ui->actionLoadFromFile, &QAction::triggered, p, &ComplexTextEditorP::loadBtnClickedSlot);

    connect(ui->actionCopy, &QAction::triggered, ui->textEdit, &QTextEdit::copy);
    connect(ui->actionCut, &QAction::triggered, ui->textEdit, &QTextEdit::cut);
    connect(ui->actionPaste, &QAction::triggered, ui->textEdit, &QTextEdit::paste);
    connect(ui->actionUndo, &QAction::triggered, ui->textEdit, &QTextEdit::undo);
    connect(ui->actionRedo, &QAction::triggered, ui->textEdit, &QTextEdit::redo);

    connect(ui->fontSizeCombo, &QComboBox::currentTextChanged, p, &ComplexTextEditorP::fontSizeChangeSlot);

    connect(qApp->clipboard(), &QClipboard::dataChanged, p, &ComplexTextEditorP::clipboardDataChangedSlot);

    connect(ui->textEdit->document(), &QTextDocument::undoAvailable,
            ui->actionUndo, &QAction::setEnabled);
    connect(ui->textEdit->document(), &QTextDocument::redoAvailable,
            ui->actionRedo, &QAction::setEnabled);

    connect(ui->textEdit, &QTextEdit::copyAvailable, this, [this](bool _isAvalaible)
    {
        ui->actionCopy->setEnabled(_isAvalaible);
        ui->actionCut->setEnabled(_isAvalaible);
    });
}

void ComplexTextEditor::on_actionFormatText_triggered()
{
    if(p->m_syntax)
    {
        p->m_syntax->formatText();
    }
}


}




