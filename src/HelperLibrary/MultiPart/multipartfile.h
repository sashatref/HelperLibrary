#pragma once

#include "../export.h"

namespace HelperLibraryNS
{

class HELPERLIBRARY_EXPORT MultiPartFile
{
public:
    QString m_name;
    QString m_fileName;
    QString m_type;
    QString m_encoding;

    QByteArray m_data;
};

}

