#pragma once

class QTranslator;
class QMainWindow;

#include <QFile>
#include <QVariant>
#include <QDir>
#include <QString>
#include <QVector>
#include <QDataStream>
#include <QBuffer>
#include <QVariantMap>
#include <QMetaEnum>

#include "export.h"

namespace Helper
{
    template<class EnumType>
    bool checkEnum(int _valueToCheck, EnumType _enumValue)
    {
        static_assert(std::is_enum<EnumType>::value == 1, "_enumValue must be Enum");
        return _valueToCheck == _enumValue;
    }

    template<class EnumType>
    bool checkEnum(EnumType _valueToCheck, EnumType _enumValue)
    {
        static_assert(std::is_enum<EnumType>::value == 1, "_enumValue must be Enum");
        return _valueToCheck == _enumValue;
    }

    template<class CheckType, class EnumType>
    bool checkEnum(CheckType _valueToCheck, const std::initializer_list<EnumType> &_arr)
    {
        for (auto &item : _arr)
        {
            if (checkEnum(_valueToCheck, item))
            {
                return true;
            }
        }
        return false;
    }

    template<class Type>
    void checkArrayOverhead(QList<Type> &_arr, int _maximumMsgCount)
    {
        const int overhead = _maximumMsgCount / 10;

        const int diff = _arr.size() - _maximumMsgCount;
        if (diff > overhead)
        {
            _arr.erase(_arr.begin(), _arr.begin() + diff);
        }
    }

    template<class T>
    void deleteAndNull(T *&_value)
    {
        delete _value;
        _value = nullptr;
    }

    template<class T>
    QVariantList toVariantList(const QList<T> &_list)
    {
        QVariantList resultList;
        for(int i = 0 ; i < _list.size(); i++)
        {
            resultList.append(QVariant::fromValue(_list[i]));
        }
        return resultList;
    }

    template<class T>
    QList<T> fromVariantList(const QVariantList &_list)
    {
        QList<T> resultList;
        for(int i = 0 ; i < _list.size(); i++)
        {
            resultList.append(_list[i].value<T>());
        }
        return resultList;
    }

    template<class T>
    QVector<QVariant> toVariantVector(const QVector<T> &_vec)
    {
        QVector<QVariant> resultVector;
        for(int i = 0 ; i < _vec.size(); i++)
        {
            resultVector.append(QVariant::fromValue(_vec[i]));
        }
        return resultVector;
    }

    template<class T>
    QVector<T> fromVariantVector(const QVector<QVariant> &_vec)
    {
        QVector<T> resultVector;
        for(int i = 0 ; i < _vec.size(); i++)
        {
            resultVector.append(_vec[i].value<T>());
        }
        return resultVector;
    }

    template<class T>
    QVariantMap toVariantMap(const QMap<QString, T> &_map)
    {
        QVariantMap resultMap;
        for(auto it = _map.begin(); it != _map.end(); ++it)
        {
            resultMap.insert(it.key(), QVariant::fromValue(it.value()));
        }
        return resultMap;
    }

    template<class T>
    QMap<QString, T> fromVariantMap(const QVariantMap &_map)
    {
        QMap<QString, T> resultMap;
        for(auto it = _map.begin(); it != _map.end(); ++it)
        {
            resultMap.insert(it.key(), it.value().value<T>());
        }
        return resultMap;
    }

    template<class T>
    void registerToQObjectConverter()
    {
        if(!QMetaType::hasRegisteredConverterFunction<T, QObject*>())
        {
            QMetaType::registerConverter<T, QObject*>([](const T &_value) -> QObject*
            {
                return const_cast<T*>(&_value);
            });
        }
    }


    template<class T>
    void registerToVectorConverter()
    {
        if(!QMetaType::hasRegisteredConverterFunction<QVariantList, QVector<T>>())
        {
            QMetaType::registerConverter<QVariantList, QVector<T>>([](const QVariantList &_list) -> QVector<T>
            {
                int _listSize =  _list.size();
                QVector<T> output;
                for(int i = 0 ; i < _listSize; i++)
                {
                    output.append(_list[i].value<T>());
                }
                return output;
            });
        }
    }
}

namespace Translate
{
/*!
     * \brief устанавливает все файлы переводов из указанного каталога с указаннм префиксом, напр. ru_
     * \param _path - путь для загрузки файлов
     * \param _prefix - префикс в название файлов, которые нужно загрузить
     * \param _translatorList - список трансляторов, для того чтоб удалить неиспользуемые
     * \param parent
     */
    void HELPERLIBRARY_EXPORT installTranslator(const QString &_path, const QString &_prefix, QList<QTranslator *> &_translatorList, QObject *parent);
    void HELPERLIBRARY_EXPORT installTranslator(const QStringList &_translationFiles, const QString &_prefix, QList<QTranslator *> &_translatroList, QObject *parent);
}


QString HELPERLIBRARY_EXPORT getCommandLine();


namespace Numerics
{
    double HELPERLIBRARY_EXPORT getRandomeDouble(int max = 20);
    double HELPERLIBRARY_EXPORT getRandomDouble(double _min, double _max = 20);
    int HELPERLIBRARY_EXPORT &fixValue(int &_value, int _min, int _max);
}


namespace Text
{
    void HELPERLIBRARY_EXPORT writeToLog(const QString &_text, QtMsgType _type);

    QString HELPERLIBRARY_EXPORT toHexAddr(void *_addr);

    template< class Class1Type, class Func1Type, class Class2Type, class Func2Type>
    void connectTextProxy(Class1Type *_obj1, Func1Type _f1, Class2Type *_obj2, Func2Type _f2, const QString _pred)
    {
        QObject::connect(_obj1, _f1, _obj2, [=](const QString &_text, QtMsgType _type)
        {
            emit (*_obj2.*_f2)(_pred + " | " + _text, _type);
        });
    }

    /*!
     * \brief formatUptime форматирует количество секунд в "Дней <dd> | Время<hh:mm:ss>
     * \param _secs
     * \return
     */
    QString HELPERLIBRARY_EXPORT formatUptime(qint64 _secs);

    /*!
     * \brief trim  в начале и в конце строки обрезает все вхождения _expr
     * \param _input
     * \param _expr
     * \return
     */
    QString HELPERLIBRARY_EXPORT &trim(QString &_input, const QString &_expr);

    /*!
     * \brief trim  в начале и в конце данных обрезает все вхождения _expr
     * \param _input
     * \param _expr
     * \return
     */
    QByteArray HELPERLIBRARY_EXPORT &trim(QByteArray &_input, const QString &_expr);

    /*!
     *  парсит текст формата "10M", "150K", "4G" в размер байтов
     */
    qint64 HELPERLIBRARY_EXPORT parseFileSize(QString _textValue);

    QString HELPERLIBRARY_EXPORT fileSizeToString(qint64 nSize);

    /*!
     * \brief unionList возвращает список значений которые есть в первом и втором списках
     * \param _list1
     * \param _list2
     * \return
     */
    QStringList HELPERLIBRARY_EXPORT unionList(const QStringList &_list1, const QStringList &_list2, Qt::CaseSensitivity _sensivity);

    QVariantMap HELPERLIBRARY_EXPORT parseJson(const QByteArray &_jsonData);
    QByteArray HELPERLIBRARY_EXPORT writeToJson(const QVariantMap &_map);

    QString HELPERLIBRARY_EXPORT enumToString(int _value,
                         const QMetaEnum &_metaEnum,
                         const QMap<QString, QString> &_namesMap = QMap<QString, QString>());

    QString HELPERLIBRARY_EXPORT enumToString(int _value,
                         const QMetaObject *_mo,
                         const QString &_enumName,
                         const QMap<QString, QString> &_namesMap = QMap<QString, QString>());

    QStringList HELPERLIBRARY_EXPORT flagsToString(int _value,
                         const QMetaEnum &_metaEnum,
                         const QMap<QString, QString> &_namesMap = QMap<QString, QString>());


    int HELPERLIBRARY_EXPORT idFromString(const QString &_valueToParse);

    QString HELPERLIBRARY_EXPORT getDateFormatString();
    QString HELPERLIBRARY_EXPORT getDateTimeFormatString();

    QString HELPERLIBRARY_EXPORT getTextWithSymbolAround(const QString &_text, int _totalLenght, const QString &_symbol);
    QString HELPERLIBRARY_EXPORT &addChars(QString &_text, const QString &_char, int _lenght);

    typedef enum {
        de1, de4, de10, deMAXSIZE
    }DigitEnding;

    QString HELPERLIBRARY_EXPORT getRandomString(int _minLenght = 8, int _maxLenght = 12);
    QDate HELPERLIBRARY_EXPORT getRandomDate();
    QTime HELPERLIBRARY_EXPORT getRandomTime();
    QDateTime HELPERLIBRARY_EXPORT getRandomeDateTime();

    bool HELPERLIBRARY_EXPORT writeToFile(const QString &_path, const QString &_text, bool _append = true, const QString &_codec = "UTF-8");
    QString HELPERLIBRARY_EXPORT readFromFile(const QString &_path, const QString &_codec = "UTF-8");

    QString HELPERLIBRARY_EXPORT textWithTimeStamp(const QString &_text);
    QString HELPERLIBRARY_EXPORT textWithDateTimeStamp(const QString &_text);


    DigitEnding HELPERLIBRARY_EXPORT GetDigitEnding(const int iValue); /* Определение склонения числа */
    QString HELPERLIBRARY_EXPORT getHourEnding(int _value);
    QString HELPERLIBRARY_EXPORT getMinuteEnding(int _value);
    QString HELPERLIBRARY_EXPORT getSecondEnding(int _value);

    /*!
     * \brief getTimeFormatted формирует текст указанного времени с склонениями: часов, минут, секунда
     * только для русского языка
     * \param _hour
     * \param _min
     * \param _sec
     * \param hideNullElements
     * \return
     */
    QString HELPERLIBRARY_EXPORT getTimeFormatted(int _hour, int _min, int _sec, bool hideNullElements = true);

    /*!
     * \brief getShortText вырезает из слова серидину и вставляет туда "...", чтоб слово стало указанной длины
     * \param _text
     * \param _size
     * \return
     */
    QString HELPERLIBRARY_EXPORT getShortText(const QString &_text, int _size);


    /*!
     * \brief getShortFilePath обрезает путь к файлу, чтоб он стал указанной длины.
     * Если строка меньше maxSize, будет возвращено без изменений.
     * Если строка не содержит пути, то будет вырезана середина слова и заменана на "..."
     * Если строка является путем, то будет заменена на "C:\...\folder1\folder2\file.name"
     * Указывая столько последних каталогов, сколько уместится в maxSize
     * Если строка является путем, но название файла больше чем maxSize, то будет заменена на
     * "C:\...\filen...end.txt"
     * \param fullPath
     * \param _maxSize
     * \return
     */
    QString HELPERLIBRARY_EXPORT getShortFilePath(const QString &fullPath, int _maxSize = 50);

    /*!
     * \brief split аналог QByteArray::split, только QChar -> QByteArray. Разбивает указанный массив
     * данных на подмассивы
     * \param _source
     * \param _splitExpr
     * \return
     */
    QList<QByteArray> HELPERLIBRARY_EXPORT split(const QByteArray &_source,
                                                 const QByteArray &sep,
                                                 QString::SplitBehavior behavior = QString::KeepEmptyParts);

    QString HELPERLIBRARY_EXPORT &trimQuotes(QString &_input);

    /*!
     * \brief isLocalhost проверяет является ли указанная строка адресом синонимом к 127.0.0.1
     * \param _addr
     * \return
     */
    bool HELPERLIBRARY_EXPORT isLocalhost(const QString &_addr);


    inline QString format(const QString &_msg)
    {
        return _msg;
    }

    template<typename T, typename... Args>
    static QString format(const QString &_msg, T _value, Args... arguments)
    {
        return format(_msg.arg(_value), arguments...);
    }

    template<typename... Args>
    static QString format(const QString &_msg, const std::wstring &_value, Args... arguments)
    {
        return format(_msg, QString::fromStdWString(_value), arguments...);
    }

    template<typename... Args>
    static QString format(const QString &_msg, const std::string &_value, Args... arguments)
    {
        return format(_msg, QString::fromStdString(_value), arguments...);
    }



    std::wstring HELPERLIBRARY_EXPORT strToWstr(const std::string &s_text);
    std::string HELPERLIBRARY_EXPORT wstrToStr(const std::wstring &s_text);

    QString HELPERLIBRARY_EXPORT makeRgbaColor(const QColor &_col);
}


namespace Files
{
    /*!
     * \brief calcHash считает хэш для массива байтов
     * \param _bData
     * \return
     */
    QString HELPERLIBRARY_EXPORT calcHash(const QByteArray &_bData);

    /*!
     * \brief calcHash считает хэш _firstBytes первых байтов файла _filePath
     * \param _filePath
     * \param _firstBytes
     * \return
     */
    QString HELPERLIBRARY_EXPORT calcHash(const QDir &_filePath, int _firstBytes = -1);
}

namespace HTTP
{
    QString HELPERLIBRARY_EXPORT createHttpDate(const QDateTime &_dateTime);
    QString HELPERLIBRARY_EXPORT createHttpDateForFile(const QString &_filePath);
}

namespace Threads
{
    void HELPERLIBRARY_EXPORT invokeOnMainThread(std::function<void()> callback, Qt::ConnectionType _type = Qt::QueuedConnection);

    QString HELPERLIBRARY_EXPORT currentThreadNum();

    class HELPERLIBRARY_EXPORT ThreadWaiter
    {
    public:

        /*
         * Возвращает true, если был запрос на выход из потока
         * false -> просто прошло время
         *
         * _ms - общее время ожидания
         * _iteration - количество итерации, на которое будет разбито общее время _ms
         */
        static bool wait(int _ms, int _iteration = 100);
    };
}

constexpr unsigned long long operator"" _kb ( unsigned long long _bytes)
{
    return _bytes * 1024;
}

constexpr unsigned long long operator"" _mb ( unsigned long long _bytes)
{
    return _bytes * 1024_kb;
}

constexpr unsigned long long operator"" _gb ( unsigned long long _bytes)
{
    return _bytes * 1024_mb;
}

constexpr unsigned long long operator"" _sec ( unsigned long long _sec)
{
    return _sec * 1000;
}

constexpr unsigned long long operator"" _min ( unsigned long long _min)
{
    return _min * 60_sec;
}

constexpr unsigned long long operator"" _hour ( unsigned long long _hour)
{
    return _hour * 60_min;
}

