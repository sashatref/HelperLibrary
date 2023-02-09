#pragma once

#include "isyntax.h"

class JsonSyntax : public ISyntax
{
    Q_OBJECT
public:
    JsonSyntax(QTextDocument *_doc);

private:
     struct HighlightingRule
     {
         QRegExp pattern;
         QTextCharFormat format;
     };
     QVector<HighlightingRule> rules;


protected:
    virtual void highlightBlock(const QString &text);
    virtual void formatText() override;
};

