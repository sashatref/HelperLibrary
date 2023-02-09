#pragma once

#include <QPrinter>

#include "../export.h"

class HELPERLIBRARY_EXPORT PdfExporter : public QObject
{
    Q_OBJECT
public:
    PdfExporter(QObject *_parent = nullptr);

    void exportFiles(const QStringList &_images, const QString &_out);

    void setPageSize(const QSize &_s);

    QSize getPageRealSize() const;

private:
    QPrinter m_printer { QPrinter::HighResolution };
};

