#include "cmdlineparser.h"

#include "textformatter.h"

#include <QDebug>

CmdLineParser::CmdLineParser():
    m_items(),
    m_error(),
    m_appName(),
    m_commandLine(),
    m_helpCommands()
{}

CmdLineParser::CmdLineParser(const CmdLineParser &_other)
{
    m_items = _other.m_items;
    m_error = _other.m_error;
    m_appName = _other.m_appName;
    m_commandLine = _other.m_commandLine;
    m_helpCommands = _other.m_helpCommands;
}

CmdLineParser &CmdLineParser::operator=(const CmdLineParser &_other)
{
    m_items = _other.m_items;
    m_error = _other.m_error;
    m_appName = _other.m_appName;
    m_commandLine = _other.m_commandLine;
    m_helpCommands = _other.m_helpCommands;
    return *this;
}

int CmdLineParser::parse(int argc, char **argv)
{
    //заполняем значениями, при которых будет возвращено значение Help
    m_helpCommands = QStringList() << "-h" << "-help" << "-?" << "/?";

    m_commandLine.clear();

    for(int i = 0 ; i < argc; i++)
    {
        m_commandLine.append(QString(argv[i]));
    }

    if(m_commandLine.size() == 0)
    {
        m_error = tr("Командная строка пустая!");
        return Error;
    }

    //получаем название исполняемого файла
    m_appName = m_commandLine[0].right(m_commandLine[0].size() - m_commandLine[0].lastIndexOf("\\") - 1);

    //если присутствует команда для вызова help'а, то выходим
    foreach (const QString &var, m_helpCommands)
    {
        if(m_commandLine.contains(var))
        {
            return Help;
        }
    }

    //узнаем был ли указан параметр в командной строке
    //для каждого ключа получаем его значения
    QString paramName;
    QStringList values;

    for(int i = 0 ; i < m_commandLine.size(); i++)
    {
        if(m_commandLine[i].indexOf("-") != 0)
        {
            values.append(m_commandLine[i]);
        }

        if(m_commandLine[i].indexOf("-") == 0 || m_commandLine.size() - 1 == i)
        {
            CmdLineItem *item = getItem(paramName);
            if(item)
            {
                item->m_value = values;
            }
            values.clear();
            paramName = m_commandLine[i];

            item = getItem(paramName);
            if(item) item->m_isFounded = true;
        }
    }


    //проверяем на наличие ошибок
    foreach (const auto &var, m_items)
    {
        if(var.m_isRequiried)
        {
            if(!var.m_isFounded)
            {
                m_error = QString(tr("Не указан обязательный параметр: -%1")).arg(var.m_name);
                return Error;
            }

            if(!var.m_canBeEmpty && var.m_value.size() == 0)
            {
                m_error = QString(tr("Не задано значение для параметра: -%1")).arg(var.m_name);
                return Error;
            }

            if(!var.m_isMultiValue && var.m_value.size() > 1)
            {
                m_error = QString(tr("Для параметра: -%1 указано слишком много значений")).arg(var.m_name);
                return Error;
            }
        } else
        {
            if(var.m_isFounded && !var.m_canBeEmpty && var.m_value.size() == 0)
            {
                m_error = QString(tr("Не задано значение для параметра: -%1")).arg(var.m_name);
                return Error;
            }

            if(!var.m_isMultiValue && var.m_value.size() > 1)
            {
                m_error = QString(tr("Для параметра: -%1 указано слишком много значений")).arg(var.m_name);
                return Error;
            }
        }

    }

    return Success;
}

QString CmdLineParser::getHelpString() const
{
    QString result = QString(tr("Программа: %1")).arg(m_appName);
    result += tr("\n\nОтмеченные знаком <!> являются обязательными\n" \
                 "Параметры:\n");

    QList<QPair<QString, QString>> textPairs;

    foreach (const auto &var, m_items)
    {
        QString text = "-" + var.m_name;

        if(var.m_isRequiried)
        {
            text += tr(" <!>");
        }

        if(!var.m_canBeEmpty)
        {
            text += tr(" <значение>");
        } else if(var.m_isMultiValue)
        {
            text += tr(" <значение, значение...>");
        }

        textPairs.append(QPair<QString, QString>(text, var.m_description));
    }

    result += TextFormatter().twoColumns(textPairs);
    return result;
}

const QString &CmdLineParser::getLastError() const
{
    return m_error;
}

const CmdLineItem *CmdLineParser::operator[](const QString &_itemName) const
{
    foreach (const auto &var, m_items)
    {
        if(var.m_name == _itemName && var.m_isFounded)
        {
            return &var;
        }
    }

    return 0;
}

const CmdLineItem *CmdLineParser::at(const QString &_itemName) const
{
    return operator [](_itemName);
}

void CmdLineParser::addItem(const CmdLineItem &_item)
{
    m_items.append(_item);
}

void CmdLineParser::addItems(const QList<CmdLineItem> &_itemList)
{
    m_items.append(_itemList);
}

CmdLineParser &CmdLineParser::operator <<(const CmdLineItem &_item)
{
    addItem(_item);
    return *this;
}

const QList<CmdLineItem> &CmdLineParser::getItems() const
{
    return m_items;
}

CmdLineItem *CmdLineParser::getItem(const QString &_paramName)
{
    for(int i = 0 ; i < m_items.size(); i++)
    {
        if("-" + m_items[i].m_name == _paramName)
        {
            return &m_items[i];
        }
    }

    return 0;
}
