#ifndef GZIPWRAPPER_H
#define GZIPWRAPPER_H

#include "../export.h"

#include <QByteArray>
#include <QIODevice>

class HELPERLIBRARY_EXPORT GZipWrapper
{
public:
    static QByteArray compressData(QByteArray input, int level);
};

#endif // GZIPWRAPPER_H
