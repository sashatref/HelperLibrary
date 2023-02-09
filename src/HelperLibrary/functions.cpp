#include "project_pch.h"
#include "functions.h"
#include "releaseassert.h"

#include <QTranslator>
#include <QCryptographicHash>
#include <QThread>
#include <QMainWindow>
#include <QJsonObject>
#include <QJsonParseError>

namespace Text
{

QString getDateFormatString()
{
    return "dd.MM.yyyy";
}

QString getDateTimeFormatString()
{
    return "dd.MM.yyyy hh:mm:ss";
}

bool writeToFile(const QString &_path, const QString &_text, bool _append, const QString &_codec)
{
    QFile file(_path);
    if(file.open(_append ? QIODevice::Append : QIODevice::WriteOnly))
    {
        QTextStream stream(&file);
        stream.setCodec(qPrintable(_codec));
        stream << _text;
        file.close();
        return true;
    }

    return false;
}

QString readFromFile(const QString &_path, const QString &_codec)
{
    QString result;

    QFile file(_path);
    if(file.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&file);
        stream.setCodec(_codec.toStdString().c_str());
        result = stream.readAll();
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

QString getRandomString(int _minLenght, int _maxLenght)
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
        randomStringLength = _minLenght + (rand() % (_maxLenght - _minLenght + 1));
    }

    QString randomString;
    for(int i=0; i < randomStringLength; ++i)
    {
        int index = qrand() % possibleCharacters.length();
        QChar nextChar = possibleCharacters.at(index);
        randomString.append(nextChar);
    }
    return randomString;
}

QDate getRandomDate()
{
    return QDate(1980 + rand() % 50, rand() % 12, rand() % 30);
}

QDateTime getRandomeDateTime()
{
    return QDateTime(getRandomDate(), getRandomTime());
}

QTime getRandomTime()
{
    return QTime(rand() %24, rand() % 60, rand() % 60);
}



QString getHourEnding(int _value)
{
    QString hourEndings[] = {"", "а", "ов"};
    return QString("час%1").arg(hourEndings[GetDigitEnding(_value)]);
}

QString getSecondEnding(int _value)
{
    QString secondEndings[] = {"а", "ы", ""};
    return QString("секунд%1").arg(secondEndings[GetDigitEnding(_value)]);
}

QString getMinuteEnding(int _value)
{
    QString minuteEndings[] = {"а", "ы", ""};
    return QString("минут%1").arg(minuteEndings[GetDigitEnding(_value)]);
}

DigitEnding GetDigitEnding(const int iValue) /* Определение склонения числа */
{
    int n = iValue % 100;

    DigitEnding r = de10;

    if (n > 4 && n < 20)
        return r;

    n = n % 10;
    if (n == 1)
        r = de1;
    else if (n > 1 && n < 5)
        r = de4;

    return r;
}



QString getShortFilePath(const QString &fullPath, int _maxSize /*= 40*/)
{
    QString tempPath = fullPath;
    tempPath.replace("/", "\\");

    //если строка нормально влазит в лимит
    if(fullPath.size() <= _maxSize)
    {
        return tempPath;
    }

    //если строка это вовсе не путь
    if(tempPath.indexOf("\\") == -1)
    {
        return getShortText(tempPath, _maxSize);
    }

    QStringList items = tempPath.split("\\");

    if(items.size() > 1)
    {
        QString first = items.first();
        QString last = items.last();
        if(last.size() > _maxSize - first.size())
        {
            QString shortLast = getShortText(last, _maxSize - first.size() - 5);
            return QString("%1\\...\\%2").arg(items.first()).arg(shortLast);
        }
    }

    int index = 0;
    int totalLenght = 0;

    for(int i = items.size() - 1 ; i > -1; i--)
    {
        totalLenght += items.at(i).size();
        if(totalLenght < _maxSize - items.first().size() - 4)
        {
            index++;
        } else
        {
            break;
        }
    }

    QStringList subArr = items.mid(items.size() - index);
    QString result = QString("%1\\...\\%2").arg(items.first()).arg(subArr.join("\\"));

    return result;
}

QString getShortText(const QString &_text, int _size)
{
    if(_text.size() <= _size)
    {
        return _text;
    }

    int mid = (_size - 3) / 2;
    int ostacha = (_size - 3) % 2;

    return QString("%1...%2").arg(_text.left(mid)).arg(_text.mid(_text.size() - mid - ostacha));
}

QString getTextWithSymbolAround(const QString &_text, int _totalLenght, const QString &_symbol)
{
    if(_totalLenght <= _text.length()) return _text;

    QString result;

    int whiteCount = _totalLenght - _text.length();

    addChars(result, _symbol, whiteCount / 2);
    result += _text;
    addChars(result, _symbol, whiteCount / 2);

    if(whiteCount % 2 != 0)
    {
        addChars(result, _symbol, 1);
    }

    return result;
}

QString &addChars(QString &_text, const QString &_char, int _lenght)
{
    for(int i = 0 ; i < _lenght; i++)
    {
        _text.append(_char);
    }

    return _text;
}

int idFromString(const QString &_valueToParse)
{
    int index1 = _valueToParse.lastIndexOf("(");
    int index2 = _valueToParse.lastIndexOf(")");
    if(index1 == -1 || index2 == -1)
    {
        return -1;
    }

    return _valueToParse.mid(index1 + 1, index2 - index1 - 1).toInt();
}

QString enumToString(int _value, const QMetaEnum &_metaEnum, const QMap<QString, QString> &_namesMap)
{
    QString keyValue = _metaEnum.valueToKey(_value);
    if(_namesMap.contains(keyValue))
    {
        keyValue = _namesMap[keyValue];
    }

    return keyValue;
}

QStringList flagsToString(int _value, const QMetaEnum &_metaEnum, const QMap<QString, QString> &_namesMap)
{
    QStringList listValues;

    for(int i = 0 ; i < _metaEnum.keyCount(); i++)
    {
        int bitMask = _metaEnum.value(i);
        QString name = _metaEnum.key(i);

        if(bitMask == 0 && _value != 0) continue;

        if(_namesMap.contains(name))
        {
            name = _namesMap[name];
        }

        bool testBit = ((_value & bitMask) == bitMask);

        if(testBit)
        {
            listValues << name;
        }
    }

    return listValues;
}

QString getTimeFormatted(int _hour, int _min, int _sec, bool hideNullElements)
{
    QString text;

    bool prevPresent = false;
    if(_hour || !hideNullElements)
    {
        text += QString("%1 %2").arg(_hour).arg(QObject::tr("ч", "часов"));
        prevPresent = true;
    }

    if(_min || !hideNullElements)
    {
        if(prevPresent) text += " ";
        text += QString("%1 %2").arg(_min).arg(QObject::tr("м", "минут"));
        prevPresent = true;
    }

    if(prevPresent) text += " ";
    text += QString("%1 %2").arg(_sec).arg(QObject::tr("с", "секунд"));

    return text;
}

QString enumToString(int _value,
                     const QMetaObject *_mo,
                     const QString &_enumName,
                     const QMap<QString, QString> &_namesMap)
{
    for(int i = _mo->enumeratorOffset(); i < _mo->enumeratorCount(); i++)
    {
        if(_mo->enumerator(i).name() == _enumName)
        {
            return enumToString(_value, _mo->enumerator(i), _namesMap);
        }
    }

    return QString();
}

QVariantMap parseJson(const QByteArray &_jsonData)
{
    QJsonParseError error;
    QJsonDocument document = QJsonDocument::fromJson(_jsonData, &error);
    return document.object().toVariantMap();
}

QByteArray writeToJson(const QVariantMap &_map)
{
    return QJsonDocument(QJsonObject::fromVariantMap(_map)).toJson();
}

QStringList unionList(const QStringList &_list1, const QStringList &_list2, Qt::CaseSensitivity _sensivity)
{
    QStringList res;

    for (int i = 0, count = _list1.size(); i < count; ++i)
    {
        if(_list2.contains(_list1[i], _sensivity))
        {
            res << _list1[i];
        }
    }

    return res;
}

QString fileSizeToString(qint64 nSize)
{
    qint64 i = 0;
    for (; nSize > 1023; nSize /= 1024, ++i) { }
    R_ASSERT_X(i < 5, "File size larger than TB");
    return QString("%1 %2").arg(nSize).arg(QObject::tr("БКМГТ").at(i));
}

qint64 parseFileSize(QString _textValue)
{
    qint64 val;
    QString sizeKey;

    QTextStream stream(&_textValue);
    stream >> val;
    stream >> sizeKey;

    const QString sizeKeys(" KMGT");

    int iterateCount = sizeKeys.indexOf(sizeKey.toUpper());
    if(iterateCount == -1) return -1;

    for(int i = 0 ; i < iterateCount; i++)
    {
        val *= 1024;
    }

    return val;
}


QString &trim(QString &_input, const QString &_expr)
{
    while(_input.startsWith(_expr))
    {
        _input.remove(0, _expr.length());
    }

    while(_input.endsWith(_expr))
    {
        _input.remove(_input.size() - _expr.length(), _expr.length());
    }

    return _input;
}

QByteArray &trim(QByteArray &_input, const QString &_expr)
{
    while(_input.startsWith(_expr.toUtf8()))
    {
        _input.remove(0, _expr.length());
    }

    while(_input.endsWith(_expr.toUtf8()))
    {
        _input.remove(_input.size() - _expr.length(), _expr.length());
    }

    return _input;
}

QList<QByteArray> split(const QByteArray &_source,
                        const QByteArray &sep,
                        QString::SplitBehavior behavior)
{

    QList<QByteArray> list;
    int start = 0;
    int extra = 0;
    int end;
    while ((end = _source.indexOf(sep, start + extra)) != -1)
    {
        if (start != end || behavior == QString::KeepEmptyParts)
        {
            list.append(_source.mid(start, end - start));
        }

        start = end + sep.size();
        extra = (sep.size() == 0 ? 1 : 0);
    }
    if (start != _source.size() || behavior == QString::KeepEmptyParts)
    {
        list.append(_source.mid(start));
    }

    return list;
}

QString &trimQuotes(QString &_input)
{
    return Text::trim(_input, "\"");
}

QString formatUptime(qint64 _secs)
{
    const qint64 secInDay = 60 * 60 * 24;

    const int days = _secs / secInDay;
    const QTime time = QTime(0,0,0).addSecs(_secs % secInDay);

    const QString dayText = QObject::tr("Дней <%1>").arg(days);
    const QString timeText = QObject::tr("Время <%1>").arg(time.toString("hh:mm:ss"));
    return QString("%1 | %2").arg(dayText).arg(timeText);
}

bool isLocalhost(const QString &_addr)
{
    QStringList items = {
        "localhost",
        "127.0.0.1"
    };

    for(const QString &item : items)
    {
        if(item.compare(_addr, Qt::CaseInsensitive) == 0)
        {
            return true;
        }
    }

    return false;
}

std::wstring strToWstr(const std::string &s_text)
{
    const int i_BUFF_SIZE = s_text.size()+1;
    wchar_t* wchBuff = new wchar_t[i_BUFF_SIZE];

    mbstowcs(wchBuff,s_text.c_str(),i_BUFF_SIZE);
    const std::wstring ws_result(wchBuff);
    delete []wchBuff;
    return ws_result;
}

std::string wstrToStr(const std::wstring &s_text) {
    const int i_BUFF_SIZE = s_text.size() + 1;
    char * chBuff = new char[i_BUFF_SIZE];

    wcstombs(chBuff,s_text.c_str(),i_BUFF_SIZE);
    const std::string s_result(chBuff);
    delete []chBuff;
    return s_result;
}

QString toHexAddr(void *_addr)
{
    return QString("%1").arg(reinterpret_cast<qintptr>(_addr), 8, 16, QLatin1Char( '0' ));
}

void writeToLog(const QString &_text, QtMsgType _type)
{
    switch(_type)
    {
    case QtDebugMsg:
        qDebug() << _text;
        break;
    case QtInfoMsg:
        qInfo() << _text;
        break;
    case QtWarningMsg:
        qWarning() << _text;
        break;
    case QtCriticalMsg:
        qCritical() << _text;
        break;
    case QtFatalMsg:
        qFatal(qPrintable(_text));
        break;
    }
}

QString makeRgbaColor(const QColor &_col)
{
    return QString("rgba(%1, %2, %3, %4)")
            .arg(_col.red())
            .arg(_col.green())
            .arg(_col.blue())
            .arg(_col.alpha());
}

}


void Translate::installTranslator(const QString &_path, const QString &_prefix, QList<QTranslator *> &_translatorList, QObject *parent)
{
    //удаляем утсновленные ранее трансляторы
    for(int i = 0 ; i < _translatorList.size(); i++)
    {
        delete _translatorList[i];
    }
    _translatorList.clear();

    //загружаем новые и добавляем их в список
    QDir trDir(_path);
    if(trDir.exists())
    {
        QStringList files = trDir.entryList(QStringList() << _prefix + "*.qm");

        for(int i = 0 ; i < files.size(); i++)
        {
            QTranslator *translator = new QTranslator(parent);
            translator->load(files[i], _path);
            qApp->installTranslator(translator);
            _translatorList.append(translator);
        }
    }
}

QString getCommandLine()
{    
    return qApp->arguments().join(" ");
}

QString Files::calcHash(const QByteArray &_bData)
{
    return QString(QCryptographicHash::hash(_bData, QCryptographicHash::Md5).toHex());
}

QString Files::calcHash(const QDir &_filePath, int _firstBytes)
{
    QCryptographicHash cryp(QCryptographicHash::Md5);
    QFile file(_filePath.path());
    if (file.open(QIODevice::ReadOnly))
    {
        QByteArray all;
        while (!file.atEnd())
        {
            QByteArray line = file.read(1024);
            cryp.addData(line);
            all+=line;

            if(_firstBytes != -1 && line.size() < 1024)
            {
                break;
            }
        }
    }
    return cryp.result().toHex().data();
}




namespace Numerics
{
double getRandomeDouble(int max)
{
    return rand() % max + (double)(rand() % 100) / (double)100;
}

int &fixValue(int &_value, int _min, int _max)
{
    if(_value > _max)
    {
        _value = _max;
    } else if(_value < _min)
    {
        _value = _min;
    }

    return _value;
}

double getRandomDouble(double _min, double _max)
{
    double offset = _max - _min;
    double randomNum = getRandomeDouble(offset);
    return _min + randomNum;
}

}

QString HTTP::createHttpDate(const QDateTime &_dateTime)
{
    QString modificationDate = QLocale::c().toString(_dateTime, "ddd, dd MMM yyyy hh:mm:ss 'GMT'");
    return modificationDate;
}

QString HTTP::createHttpDateForFile(const QString &_filePath)
{
    return createHttpDate(QFileInfo(_filePath).lastModified());
}

bool Threads::ThreadWaiter::wait(int _ms, int _iteration)
{
    if(QThread::currentThread()->isInterruptionRequested())
    {
        return true;
    }

    for(int i = 0 ; i < _iteration; i++)
    {
        if(QThread::currentThread()->isInterruptionRequested())
        {
            return true;
        }

        QThread::msleep(_ms / _iteration);
    }

    return false;
}

QString Threads::currentThreadNum()
{
    return QString("0x%1").arg((qintptr)QThread::currentThreadId(), 8, 16, QLatin1Char( '0' ));
}

void Threads::invokeOnMainThread(std::function<void ()> callback, Qt::ConnectionType _type)
{
    if(_type == Qt::BlockingQueuedConnection)
    {
        if(qApp->thread() == QThread::currentThread())
        {
            R_ASSERT_X(false, "DEADLOCK HERE");
        }
    }

    // any thread
    QTimer* timer = new QTimer();
    timer->moveToThread(qApp->thread());
    timer->setSingleShot(true);
    QObject::connect(timer, &QTimer::timeout, [=]()
    {
        // main thread
        callback();
        timer->deleteLater();
    });
    QMetaObject::invokeMethod(timer, "start", _type, Q_ARG(int, 0));
}
