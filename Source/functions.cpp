#include "functions.h"

#include <QTextStream>
#include <QFile>
#include <QTime>

namespace Text
{

bool writeToFile(const QString &_path, const QString &_text, bool _append)
{
    QFile file(_path);
    if(file.open(_append ? QIODevice::Append : QIODevice::WriteOnly))
    {
        QTextStream stream(&file);
        stream << _text;
        file.close();
        return true;
    }

    return false;
}

QString readFromFile(const QString &_path)
{
    QString result;

    QFile file(_path);
    if(file.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&file);
        stream >> result;
        file.close();
    }

    return result;
}

QString textWithDateTimeStamp(const QString &_text)
{
    return QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss") + " | " + _text;
}

QString textWithTimeStamp(const QString &_text)
{
    return QTime::currentTime().toString("hh:mm:ss") + " | " + _text;
}
}


