#include "multipartparser.h"
#include "../functions.h"


namespace HelperLibraryNS
{

MultiPartParser::MultiPartParser()
{

}

MultiPartParser::~MultiPartParser()
{

}

bool parseContentDispotiion(const QString &_line, QString &_name, QString &_fileName)
{
    if(!_line.startsWith("Content-disposition"))
    {
        return false;
    }

    QStringList tokens = _line.split(";");
    for(const QString &item: tokens)
    {
        QStringList values = item.split("=");
        if(values.size() == 2)
        {
            if(values[0].trimmed() == "name")
            {
                _name = Text::trimQuotes(values[1]);
            }

            if(values[0].trimmed() == "filename")
            {
                _fileName = Text::trimQuotes(values[1]);
            }
        }
    }

    return true;
}

bool parseParam(const QString &_line, const QString &_paramName, QString &_value)
{
    if(!_line.startsWith(_paramName))
    {
        return false;
    }

    QStringList tokens = _line.split(":");

    if(tokens.size() == 2)
    {
        _value = tokens[1].trimmed();
    }

    return true;
}

bool parseContentType(const QString &_line, QString &_contentType)
{
    return parseParam(_line, "Content-Type", _contentType);
}

bool parseContentEncoding(const QString &_line, QString &_contentType)
{
    return parseParam(_line, "Content-Transfer-Encoding", _contentType);
}

void parseSection(QString &_description, QByteArray &_data, const QByteArray &_source)
{
    int index = _source.indexOf("\r\n\r\n");

    if(index == -1)
    {
        return;
    }

    _description = _source.mid(0, index);
    _data = _source.mid(index, _source.length());
}

bool MultiPartParser::parse(const QByteArray &_data)
{
    QTextStream stream(const_cast<QByteArray*>(&_data), QIODevice::ReadOnly);
    QString uniqueName = stream.readLine();

    if(uniqueName.isEmpty()) return false;

    QVariantMap props;

    QList<QByteArray> tokens = Text::split(_data, uniqueName.toUtf8());

    for(const QByteArray &_token : tokens)
    {
        QString descriptionSection;
        QByteArray dataSection;
        parseSection(descriptionSection, dataSection, _token);

        Text::trim(descriptionSection, "\r\n");
        Text::trim(dataSection, "\r\n");

        QString name;
        QString fileName;
        QString contentType;
        QString contentEncoding;

        QStringList descrTokens = descriptionSection.split("\r\n");
        for(const QString &descrItem : descrTokens)
        {
            if(parseContentDispotiion(descrItem, name, fileName))
            {
                props["name"] = name;
                props["filename"] = fileName;
            } else

            if(parseContentType(descrItem, contentType))
            {
                props["contentType"] = contentType;
            } else

            if(parseContentEncoding(descrItem, contentEncoding))
            {
                props["ContentEncoding"] = contentEncoding;
            }
        }

        if(props["filename"].toString().isEmpty())
        {
            m_props[props["name"].toString()] = dataSection;
            props.clear();
        } else
        {
            MultiPartFile f;
            f.m_data = dataSection;
            f.m_fileName = props["filename"].toString();
            f.m_encoding = props["ContentEncoding"].toString();
            f.m_name = props["name"].toString();
            f.m_type = props["contentType"].toString();

            m_files.append(f);
            props.clear();
        }
    }


    return true;
}

QVariantMap MultiPartParser::getProperties() const
{
    return m_props;
}

QList<MultiPartFile> MultiPartParser::getFiles() const
{
    return m_files;
}

}
