/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the QtGui module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL21$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 or version 3 as published by the Free
** Software Foundation and appearing in the file LICENSE.LGPLv21 and
** LICENSE.LGPLv3 included in the packaging of this file. Please review the
** following information to ensure the GNU Lesser General Public License
** requirements will be met: https://www.gnu.org/licenses/lgpl.html and
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** As a special exception, The Qt Company gives you certain additional
** rights. These rights are described in The Qt Company LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef ZipReader_H
#define ZipReader_H

#include <QtCore/qglobal.h>

#ifndef QT_NO_TEXTODFWRITER

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists for the convenience
// of the ZipReader class.  This header file may change from
// version to version without notice, or even be removed.
//
// We mean it.
//

#include "../export.h"
#include <QtCore/qdatetime.h>
#include <QtCore/qfile.h>
#include <QtCore/qstring.h>

QT_BEGIN_NAMESPACE

class ZipReaderPrivate;

class HELPERLIBRARY_EXPORT ZipReader
{
public:
    explicit ZipReader(const QString &fileName, QIODevice::OpenMode mode = QIODevice::ReadOnly );

    explicit ZipReader(QIODevice *device);
    ~ZipReader();

    QIODevice* device() const;

    bool isReadable() const;
    bool exists() const;

    struct FileInfo
    {
        FileInfo() Q_DECL_NOTHROW
            : isDir(false), isFile(false), isSymLink(false), crc(0), size(0)
        {}

        bool isValid() const Q_DECL_NOTHROW { return isDir || isFile || isSymLink; }

        QString filePath;
        uint isDir : 1;
        uint isFile : 1;
        uint isSymLink : 1;
        QFile::Permissions permissions;
        uint crc;
        qint64 size;
        QDateTime lastModified;
    };

    QVector<FileInfo> fileInfoList() const;
    int count() const;

    FileInfo entryInfoAt(int index) const;
    QByteArray fileData(const QString &fileName) const;
    bool extractAll(const QString &destinationDir) const;

    enum Status {
        NoError,
        FileReadError,
        FileOpenError,
        FilePermissionsError,
        FileError
    };

    Status status() const;

    void close();

private:
    ZipReaderPrivate *d;
    Q_DISABLE_COPY(ZipReader)
};
Q_DECLARE_TYPEINFO(ZipReader::FileInfo, Q_MOVABLE_TYPE);
Q_DECLARE_TYPEINFO(ZipReader::Status, Q_PRIMITIVE_TYPE);

QT_END_NAMESPACE

#endif // QT_NO_TEXTODFWRITER
#endif // ZipReader_H
