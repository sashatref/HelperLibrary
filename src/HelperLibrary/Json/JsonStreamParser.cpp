#include "JsonStreamParser.h"



JsonStreamParser::JsonStreamParser(QObject *_parent):
    QObject(_parent)
{

}

void JsonStreamParser::processData(const QByteArray &_data)
{
    m_recv_buffer += _data;
    m_recv_buffer = processBuffer(m_recv_buffer.trimmed());
}

QByteArray JsonStreamParser::processBuffer(const QByteArray &buf)
{
    if(buf.size() == 0)
    {
        return {};
    }

    if (buf[0] != '{') {
        return {};
    }

    bool in_string = false, in_esc = false;
    int brace_nesting_level = 0;
    int start = 0;

    int i = 0;
    while (i < buf.length() ) {
        const char curr_ch = buf[i++];

        if (curr_ch == '"' && !in_esc) {
            in_string = !in_string;
            continue;
        }

        if (!in_string) {
            if (curr_ch == '{')
                ++brace_nesting_level;
            else if (curr_ch == '}') {
                --brace_nesting_level;
                //                    assert(brace_nesting_level >= 0);

                if (brace_nesting_level == 0) {
                    QJsonDocument doc = QJsonDocument::fromJson(buf.mid(start, i - start));
                    if (doc.isObject())
                    {
                        emit objectReceived(doc.toVariant());
                    }
                    start = i;
                    continue;
                }
            }
        } else {
            // in_string == true, maintain in_esc flag (which can only be latched true when in_string)
            if (curr_ch == '\\' && !in_esc)
            {
                in_esc = true;
            }
            else
            {
                in_esc = false;
            }
        }
    }
    return start > 0 ? buf.mid(start) : buf;
}
