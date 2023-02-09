#include "Randomizer.h"

static double getRandomeDouble(int max)
{
    return qrand() % max + (double)(qrand() % 100) / (double)100;
}

int &Randomizer::rand(int &_v, int _min, int _max)
{
    _v = _min + qrand() % (( _max + 1 ) - _min);
    return _v;
}

double & Randomizer::rand(double &_v, double _min, double _max)
{
    double offset = _max - _min;
    double randomNum = getRandomeDouble(offset);
    _v = _min + randomNum;
    return _v;
}

QString& Randomizer::rand(QString &_v, int _minLenght, int _maxLenght)
{
    const QString possibleCharacters("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789");

    if(_minLenght > _maxLenght)
    {
        _minLenght = _maxLenght;
    }

    int randomStringLength;
    if(_minLenght == _maxLenght)
    {
        randomStringLength = _minLenght;
    } else
    {
        randomStringLength = _minLenght + (qrand() % (_maxLenght - _minLenght + 1));
    }

    QString randomString;
    for(int i=0; i < randomStringLength; ++i)
    {
        int index = qrand() % possibleCharacters.length();
        QChar nextChar = possibleCharacters.at(index);
        randomString.append(nextChar);
    }
    _v = randomString;
    return _v;
}

QDate& Randomizer::rand(QDate &_v)
{
    _v = QDate(1980, 1, 1);
    int days = 0;
    rand(days, 0, 10000);
    _v.addDays(days);
    return _v;
}

QDateTime& Randomizer::rand(QDateTime &_v)
{
    QDate d;
    QTime t;
    _v = QDateTime(rand(d), rand(t));
    return _v;
}

QTime &Randomizer::rand(QTime &_v)
{
    _v = QTime(qrand() % 24, qrand() % 60, qrand() % 60);
    return _v;
}

bool &Randomizer::rand(bool &_v)
{
    int number = 0;
    rand(number, 0, 1);

    _v = number;
    return _v;
}

QRect &Randomizer::rand(QRect &_v)
{
    QPoint p;
    QSize s;
    rand(p);
    rand(s);
    _v = QRect(p, s);
    return _v;
}

QPoint &Randomizer::rand(QPoint &_v)
{
    int x = 0;
    int y = 0;
    rand(x);
    rand(y);
    _v = { x, y };
    return _v;
}

QSize &Randomizer::rand(QSize &_v)
{
    int w = 0;
    int h = 0;
    rand(w);
    rand(h);
    _v = { w, h };
    return _v;
}

std::string &Randomizer::rand(std::string &_v, int _minLen, int _maxLen)
{
    QString str;
    rand(str, _minLen, _maxLen);
    _v = str.toStdString();
    return _v;
}

char &Randomizer::rand(char &_v, char _min, char _max)
{
    int v = 0;
    rand(v, _min, _max);
    _v = static_cast<char>(v);
    return _v;
}

QByteArray &Randomizer::rand(QByteArray &_v, int _minLen, int _maxLen)
{
    int count = 10;
    rand(count, _minLen, _maxLen);

    _v.clear();
    _v.resize(count);
    for(int i = 0 ; i < count; i++)
    {
        char ch = 0;
        rand(ch);
        _v[i] = ch;
    }

    return _v;
}
