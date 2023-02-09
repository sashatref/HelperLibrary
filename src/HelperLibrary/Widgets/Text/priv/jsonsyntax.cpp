#include "jsonsyntax.h"


JsonSyntax::JsonSyntax(QTextDocument *_doc):
    ISyntax(_doc)
{
    HighlightingRule rule;

    //numbers
    rule.pattern = QRegExp("([-0-9.]+)(?!([^\"]*\"[\\s]*\\:))");
    rule.format.setForeground(Qt::darkGreen);
    rules.append(rule);

    //key
    rule.pattern = QRegExp ("(\"[^\"]*\")");
    rule.format.setForeground(QColor(0x2E75B6));
    rules.append(rule);

    //value
    rule.pattern = QRegExp(":\\s*([\"](?:[^\"])*[\"])");
    rule.format.setForeground(QColor(0xA34246));
    rules.append(rule);

    //reserved words
    rule.pattern = QRegExp("(true|false|null)(?!\"[^\"]*\")");
    rule.format.setForeground(Qt::blue);
    rules.append(rule);
}

void JsonSyntax::highlightBlock(const QString &text)
{
    foreach (const HighlightingRule &rule, rules) {
        QRegExp expression(rule.pattern);
        int index = expression.indexIn(text);

        while (index >= 0) {
            index = expression.pos(1);
            int length = expression.cap(1).length();
            setFormat(index, length, rule.format);
            index = expression.indexIn(text, index + length);
        }
    }
}


void JsonSyntax::formatText()
{

}
