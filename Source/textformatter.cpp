#include "textformatter.h"

#include <QString>

QString TextFormatter::twoColumns(const QList<QPair<QString, QString>> &_text) const
{
    QString result;

    int firstColumnWidth = calcWidth(_text);
    int widthForSecondColumn = m_totalCharWidth - m_firstColumnPreSpaces - firstColumnWidth - m_secondColumnPreSpaces;

    foreach (const auto &var, _text)
    {
        result += getSpaces(m_firstColumnPreSpaces)
                + var.first
                + getSpaces(firstColumnWidth - var.first.length())
                + getSpaces(m_secondColumnPreSpaces)
                + splitString(var.second, m_totalCharWidth, m_totalCharWidth - widthForSecondColumn);
    }

    return result;
}

QString TextFormatter::getSpaces(int _count)
{
    QString result;
    for(int i = 0; i < _count; i++)
    {
        result += " ";
    }
    return result;
}

int TextFormatter::calcWidth(const QList<QPair<QString, QString> > &_text)
{
    int result = 0;

    foreach (const auto &var, _text)
    {
        if(var.first.length() > result)
        {
            result = var.first.length();
        }
    }

    return result;
}

QString TextFormatter::splitString(const QString &_text, int _totalWidth, int _offset)
{
    QString result;
    int textWidth = _totalWidth - _offset;

    int count = (_text.length() / textWidth) + 1;
    for(int i = 0 ; i < count; i++)
    {
        result += _text.mid(i * textWidth, textWidth);
        result += "\n";
        if(i != count - 1)
        {
            result += getSpaces(_offset);
        }

    }

    //result += "\n";

    return result;
}


