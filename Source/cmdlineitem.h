#pragma once

#include <QString>
#include <QStringList>

class CmdLineItem
{
public:
    friend class CmdLineParser;

    CmdLineItem(const QString &_name = "",
                bool _isRequiried = false,
                bool _isMultiValue = false,
                bool _canBeEmpty = true,
                const QString &_description = "");

    QString m_name;         ///< название параметра, в командной строке необходимо указывать как -<название> <значение>
    QString m_description;  ///<описание параметра, которое будет показано при вызове хелпа
    bool m_isRequiried;     ///<является ли параметр обязательным
    bool m_isMultiValue;    ///<можно ли указывать несколько значений, значения указываются через пробел
    bool m_canBeEmpty;      ///<может ли параметр быть без значений

    const QStringList &getValue() const;    ///<получить список значений для данного параметра
private:
    QStringList m_value;    ///<список значения данного параметра
    int m_index;            ///<какое место занимает в списке всех параметров
    bool m_isFounded;       ///<найден ли параметр в коммандной строке
};

