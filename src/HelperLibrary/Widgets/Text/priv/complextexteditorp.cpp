#include "complextexteditorp.h"
#include "ui_complextexteditor.h"

#include "jsonsyntax.h"
#include "xmlsyntax.h"

#include <QClipboard>
#include <QMimeData>

namespace HelperLibraryNS
{

const QString plainTextName = "plain text";

ComplexTextEditorP::ComplexTextEditorP(ComplexTextEditor *_q) :
    q(_q)
{

}

ComplexTextEditorP::~ComplexTextEditorP()
{
    if(m_syntax)
    {
        delete m_syntax;
        m_syntax = nullptr;
    }
}

void ComplexTextEditorP::createActions()
{
    QStringList types = m_factory.keys();

    m_actionGroup = new QActionGroup(this);

    for(auto &type : types)
    {
        QAction *act = new QAction(q);
        act->setText(type);
        act->setProperty("name", type);
        act->setCheckable(true);

        connect(act, &QAction::triggered, this, &ComplexTextEditorP::onActionClicked);

        m_actionGroup->addAction(act);
        q->ui->menuSyntax->addAction(act);
    }
}


void ComplexTextEditorP::loadBtnClickedSlot()
{
    QString path = QFileDialog::getOpenFileName(q,
                                                tr("Выберите файл"),
                                                m_lastPath,
                                                "*.*");
    if(path.isEmpty())
    {
        return;
    }

    m_lastPath = path;

    QFile f(m_lastPath);
    if(!f.open(QIODevice::ReadOnly))
    {
        QMessageBox::warning(q, tr("Ошибка"), tr("Ошибка чтения файла [%1] - [%2]")
                             .arg(m_lastPath)
                             .arg(f.errorString()));
        return;
    }

    QTextStream stream(&f);
    stream.setCodec("UTF-8");
    q->setText(stream.readAll());
    f.close();
}

void ComplexTextEditorP::saveBtnClickedSlot()
{
    QString path = QFileDialog::getSaveFileName(q,
                                                tr("Выберите файл"),
                                                m_lastPath,
                                                "*.*");
    if(path.isEmpty())
    {
        return;
    }

    m_lastPath = path;

    QFile f(m_lastPath);
    if(!f.open(QIODevice::WriteOnly))
    {
        QMessageBox::warning(q, tr("Ошибка"), tr("Ошибка записи в файл [%1] - [%2]")
                             .arg(m_lastPath)
                             .arg(f.errorString()));
        return;
    }

    QTextStream stream(&f);
    stream.setCodec("UTF-8");
    stream << q->getText();
    f.close();
}

void ComplexTextEditorP::actionNewSlot()
{

}

void ComplexTextEditorP::actionUndoSlot()
{

}

void ComplexTextEditorP::actionRedoSlot()
{

}

void ComplexTextEditorP::actionCutSlot()
{

}

void ComplexTextEditorP::actionCopySlot()
{

}

void ComplexTextEditorP::actionPasteSlot()
{

}

void ComplexTextEditorP::onActionClicked()
{
    QAction *act = qobject_cast<QAction*>(sender());
    useType(act->property("name").toString());
}

void ComplexTextEditorP::fontSizeChangeSlot(const QString &_val)
{
    bool isOk = false;
    const int size = _val.toInt(&isOk);

    if(isOk)
    {
        QFont f = q->ui->textEdit->font();
        f.setPointSize(size);
        q->ui->textEdit->setFont(f);
    }
}

void ComplexTextEditorP::clipboardDataChangedSlot()
{
    if (const QMimeData *md = QApplication::clipboard()->mimeData())
    {
        q->ui->actionPaste->setEnabled(md->hasText());
    }
}

void ComplexTextEditorP::useType(QString _type)
{
    if(m_syntax)
    {
        delete m_syntax;
    }

    if(_type.isEmpty())
    {
        _type = plainTextName;
    }

    m_syntax = m_factory.create(_type);
    m_lastHighlighterName = _type;
}

void ComplexTextEditorP::setActionChecked(const QString &_type)
{
    for(QAction *act : m_actionGroup->actions())
    {
        if(act->property("name").toString() == _type)
        {
            act->setChecked(true);
            return;
        }
    }
}

void ComplexTextEditorP::registerFactoryFunc()
{
    m_factory.add(plainTextName, []{return nullptr;});
    m_factory.add("json", [=]{return new JsonSyntax(q->ui->textEdit->document());});
    m_factory.add("xml", [=]{return new XmlSyntax(q->ui->textEdit->document());});
}


}
