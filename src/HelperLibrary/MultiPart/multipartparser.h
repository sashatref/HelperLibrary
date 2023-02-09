#pragma once

#include "multipartfile.h"

namespace HelperLibraryNS
{

class HELPERLIBRARY_EXPORT MultiPartParser
{
public:
    MultiPartParser();
    ~MultiPartParser();

    bool parse(const QByteArray &_data);

    QVariantMap getProperties() const;

    QList<MultiPartFile> getFiles() const;

private:
    QVariantMap m_props;
    QList<MultiPartFile> m_files;
};

}

