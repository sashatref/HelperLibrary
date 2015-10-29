#pragma once

#include <QList>
#include <QPair>

class QString;

/*!
 * \brief выстраивает текст в две колонки
 * удобно для вывода файла помощи в консоль
 */
class TextFormatter
{
public:
    /*!
     * \brief TextFormatter
     * \param _totalCharWith - ширина консоли - 1
     * \param _fistColumnPreScapes - отступ перед первой колонкой
     * \param _secondColumnPreScapes - отступ между первой и второй колонкой
     */
    TextFormatter(int _totalCharWith = 79,
                  int _fistColumnPreScapes = 4,
                  int _secondColumnPreScapes = 2):
        m_totalCharWidth(_totalCharWith),
        m_firstColumnPreSpaces(_fistColumnPreScapes),
        m_secondColumnPreSpaces(_secondColumnPreScapes)
    {}

    /*!
     * \brief twoColumns
     * \param _text список пар строк для вывода
     * \return форматированный текст
     */
    QString twoColumns(const QList<QPair<QString, QString>> &_text) const;

private:
    int m_totalCharWidth;
    int m_firstColumnPreSpaces;
    int m_secondColumnPreSpaces;

    static int calcWidth(const QList<QPair<QString, QString> > &_text);
    static QString splitString(const QString &_text, int _totalWidth, int _offset);
    static QString getSpaces(int _count);
};


