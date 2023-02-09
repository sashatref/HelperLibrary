#include "converfuncimpl.h"

namespace SerializerQt
{

QString ConverterInt::toString(const QVariant &_v, QString &_typeName) const
{
    _typeName = "int";
    return QString::number(_v.toInt());
}

QVariant ConverterInt::fromString(const QString &_in) const
{
    QVariant result = _in.toInt();
    return result;
}

QString ConverterString::toString(const QVariant &_v, QString &_typeName) const
{
    _typeName = "QString";
    return _v.toString();
}

QVariant ConverterString::fromString(const QString &_in) const
{
    return _in;
}

QString ConverterDouble::toString(const QVariant &_v, QString &_typeName) const
{
    _typeName = "double";
    return QString::number(_v.toDouble(), 'f', 6);
}

QVariant ConverterDouble::fromString(const QString &_in) const
{
    return _in.toDouble();
}

QString ConverterBool::toString(const QVariant &_v, QString &_typeName) const
{
    _typeName = "bool";
    return QString::number(_v.toBool());
}

QVariant ConverterBool::fromString(const QString &_in) const
{
    return (bool)_in.toInt();
}

QString ConverterByteArray::toString(const QVariant &_v, QString &_typeName) const
{
    _typeName = "QByteArray";
    return byteArrayToString(_v.toByteArray());
}

QVariant ConverterByteArray::fromString(const QString &_in) const
{
    return stringToByteArray(_in);
}

QString ConverterByteArray::byteArrayToString(const QByteArray &_data)
{
    QStringList resultList;
    for(int i = 0 ; i < _data.size(); i++)
    {
        resultList.append(QString::number(_data.at(i), 16).right(2));
    }
    return resultList.join(",");
}

QByteArray ConverterByteArray::stringToByteArray(const QString &_string)
{
    QByteArray result;
    QStringList bytes = _string.split(",");
    for(int i = 0 ; i < bytes.size(); i++)
    {
        result.append(bytes.at(i).toInt(0, 16));
    }
    return result;
}

QString ConverterDate::toString(const QVariant &_v, QString &_typeName) const
{
    _typeName = "QDate";
    QDate time = _v.toDate();
    return time.toString("dd.MM.yyyy");
}

QVariant ConverterDate::fromString(const QString &_in) const
{
    QDate date = QDate::fromString(_in, "dd.MM.yyyy");
    return date;
}

QString ConverterDateTime::toString(const QVariant &_v, QString &_typeName) const
{
    _typeName = "QDateTime";
    QDateTime time = _v.toDateTime();
    return time.toString("dd.MM.yyyy hh.mm.ss");
}

QVariant ConverterDateTime::fromString(const QString &_in) const
{
    QDateTime dateTime = QDateTime::fromString(_in, "dd.MM.yyyy hh.mm.ss");
    return dateTime;
}

QString ConverterTime::toString(const QVariant &_v, QString &_typeName) const
{
    _typeName = "QTime";
    QTime time = _v.toTime();
    return time.toString("hh.mm.ss");
}

QVariant ConverterTime::fromString(const QString &_in) const
{
    QTime time = QTime::fromString(_in, "hh.mm.ss");
    return time;
}

QString ConverterRect::toString(const QVariant &_v, QString &_typeName) const
{
    _typeName = "QRect";
    QRect rect = _v.toRect();
    QString rectString = QString("%1, %2, %3, %4")
            .arg(rect.top())
            .arg(rect.left())
            .arg(rect.width())
            .arg(rect.height());

    return rectString;
}

QVariant ConverterRect::fromString(const QString &_in) const
{
    QRect rect;
    QStringList values = _in.split(",");
    if(values.size() == 4)
    {
        rect.setTop(values[0].toInt());
        rect.setLeft(values[1].toInt());
        rect.setWidth(values[2].toInt());
        rect.setHeight(values[3].toInt());
    }
    return rect;
}

QString ConverterSize::toString(const QVariant &_v, QString &_typeName) const
{
    _typeName = "QSize";
    QSize size = _v.toSize();
    QString sizeString = QString("%1, %2")
            .arg(size.width())
            .arg(size.height());

    return sizeString;
}

QVariant ConverterSize::fromString(const QString &_in) const
{
    QSize size;
    QStringList values = _in.split(",");
    if(values.size() == 2)
    {
        size.setWidth(values[0].toInt());
        size.setHeight(values[1].toInt());
    }
    return size;
}

QString ConverterColor::toString(const QVariant &_v, QString &_typeName) const
{
    _typeName = "QColor";
    QColor color = _v.value<QColor>();
    return QString::number(color.rgba(), 16);
}

QVariant ConverterColor::fromString(const QString &_in) const
{
    QColor color;
    color.setRgba(_in.toUInt(0, 16));
    return QVariant::fromValue(color);
}

QString ConverterFont::toString(const QVariant &_v, QString &_typeName) const
{
    _typeName = "QFont";
    QFont font = _v.value<QFont>();
    return font.toString();
}

QVariant ConverterFont::fromString(const QString &_in) const
{
    QFont font;
    font.fromString(_in);
    return QVariant::fromValue(font);
}

QString ConverterUrl::toString(const QVariant &_v, QString &_typeName) const
{
    _typeName = "QUrl";
    QUrl url = _v.toUrl();
    return url.toString();
}

QVariant ConverterUrl::fromString(const QString &_in) const
{
    QUrl url;
    url = _in;
    return QVariant::fromValue(url);
}

QString ConverterPoint::toString(const QVariant &_v, QString &_typeName) const
{
    _typeName = "QPoint";
    QPoint point = _v.value<QPoint>();
    return QString("%1;%2").arg(point.x()).arg(point.y());
}

QVariant ConverterPoint::fromString(const QString &_in) const
{
    QPoint point;

    QStringList values = _in.split(";");
    if(values.size() == 2)
    {
        point.setX(values.first().toInt());
        point.setY(values.last().toInt());
    }
    return QVariant::fromValue(point);
}

QString ConverterPointF::toString(const QVariant &_v, QString &_typeName) const
{
    _typeName = "QPointF";
    QPointF point = _v.value<QPointF>();
    return QString("%1;%2").arg(point.x()).arg(point.y());
}

QVariant ConverterPointF::fromString(const QString &_in) const
{
    QPointF point;

    QStringList values = _in.split(";");
    if(values.size() == 2)
    {
        point.setX(values.first().toDouble());
        point.setY(values.last().toDouble());
    }
    return QVariant::fromValue(point);
}

}
