#pragma once

#include <QList>
#include <QStringList>
#include <QObject>

#include "cmdlineitem.h"

/*!
 * \brief The CmdLineParser class
 * парсит командную строку и возвращает значения для каждого из параметров
 * генерирует текст помощи-описания для каждого параметра
 * проверяет правильность указания параметров
 * доступна возможность использовать параметры без значений, с 1 значением или несколькими значениями
 * возможность делать некоторые параметры необязательными
 */

class CmdLineParser : public QObject
{
public:
    enum
    {
        Error,
        Help,
        Success
    };

    CmdLineParser();
    CmdLineParser(const CmdLineParser &_other);
    CmdLineParser &operator=(const CmdLineParser &_other);
    CmdLineParser &operator <<(const CmdLineItem &_item);

    /*!
     * \brief парсит командную строку и выдает результат парсинга
        Error - если командная строка заполнена неверно, текст ошибки можно получить через getLastError
        Help - если найдена одна из команд для показа хелпа
        Succes - все в порядке
     */
    int parse(int argc, char** argv);

    /*!
     * \brief добавить один элемент CmdLineItem
     */
    void addItem(const CmdLineItem &_item);

    /*!
     * \brief добавить список QList<CmdLineItem>
     */
    void addItems(const QList<CmdLineItem> &_itemList);

    /*!
     * \brief получить список всех CmdLineItem
     */
    const QList<CmdLineItem> &getItems() const;

    /*!
     * \brief возвращает строку хелпа, построенную на освнование списка CmdLineItem
     */
    QString getHelpString() const;

    /*!
     * \brief возвращает последнюю ошибку
     */
    const QString &getLastError() const;

    /*!
     * \brief возвращает указатель на CmdLineItem по имени.
     * имя нужно указывать без дефиса
     * если данного параметра нет, или он является необязательным и его не указали, то будет возвращен 0
     * указатель становится невалидным после уничтожения объекта CmdLineParser
     */
    const CmdLineItem *operator[](const QString &_itemName) const;

    /*!
     * \brief копия функциональности оператора [], который можно использовать для указателей
     */
    const CmdLineItem *at(const QString &_itemName) const;

private:
    QList<CmdLineItem> m_items;     ///<список параметров CmdLineItem
    QString m_error;                ///<последняя ошибка
    QString m_appName;              ///<название приложения
    QStringList m_commandLine;      ///<список аргументов командной строки
    QStringList m_helpCommands;     ///<список аргументов, при обнаружение которых будет показан хелп

    CmdLineItem *getItem(const QString &_paramName);    ///<возвращает указатель на параметр по имени,
                                                        ///<без учета был он указан пользователем
};


