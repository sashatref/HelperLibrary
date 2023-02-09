#include "PdfExporter.h"

#include <QTextDocument>

PdfExporter::PdfExporter(QObject *_parent):
    QObject(_parent)
{
    m_printer.setOrientation(QPrinter::Landscape);
    m_printer.setOutputFormat(QPrinter::PdfFormat);
    m_printer.setFullPage(true);
    m_printer.setPaperSize(QSize(2160, 3840), QPrinter::DevicePixel);
    m_printer.setMargins(QPrinter::Margins {0,0,0,0});
}

void PdfExporter::exportFiles(const QStringList &_images, const QString &_out)
{
    QStringList htmlFileTags;

    for(auto &it : _images)
    {
        htmlFileTags << QString("<img src='%1' />").arg(it);
    }

    QString text = QString("<html> <head></head> <body> %1 </body>  </html>").arg(htmlFileTags.join("\n"));

    m_printer.setOutputFileName(_out);

    QTextDocument doc;
    doc.setPageSize(QSizeF(m_printer.pageRect().size()));
    doc.setDocumentMargin(0);
    doc.setHtml(text);

    doc.print(&m_printer);
}

void PdfExporter::setPageSize(const QSize &_s)
{
    m_printer.setPaperSize(QSize(_s.height(), _s.width()), QPrinter::DevicePixel);
}

QSize PdfExporter::getPageRealSize() const
{
    return m_printer.pageRect().size();
}

