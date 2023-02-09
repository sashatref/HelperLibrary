#pragma once

#include <QSyntaxHighlighter>

class ISyntax : public QSyntaxHighlighter
{
public:
    ISyntax(QTextDocument *_doc);

    virtual void formatText()
    {

    }
};
