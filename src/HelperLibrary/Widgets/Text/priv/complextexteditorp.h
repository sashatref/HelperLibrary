#pragma once

#include "objectfactory.h"
#include "../complextexteditor.h"
#include "isyntax.h"

namespace HelperLibraryNS
{

class ComplexTextEditorP : public QObject
{
    Q_OBJECT
public:
    ComplexTextEditor *q;
    ComplexTextEditorP(ComplexTextEditor *_q);
    ~ComplexTextEditorP();

    QString m_lastPath;
    QString m_lastHighlighterName;

    ISyntax *m_syntax = nullptr;

    ObjectFactory<ISyntax, QString> m_factory;

    QActionGroup *m_actionGroup = nullptr;

    void createActions();
    void useType(QString _type);
    void setActionChecked(const QString &_type);

    void registerFactoryFunc();

public slots:
    void loadBtnClickedSlot();
    void saveBtnClickedSlot();

    void actionNewSlot();
    void actionUndoSlot();
    void actionRedoSlot();
    void actionCutSlot();
    void actionCopySlot();
    void actionPasteSlot();

    void onActionClicked();

    void fontSizeChangeSlot(const QString &_val);

    void clipboardDataChangedSlot();
};

}
