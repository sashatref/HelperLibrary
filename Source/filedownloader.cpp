#include "filedownloader.h"

#include <QNetworkReply>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QDebug>
#include <QEventLoop>

FileDownloader::FileDownloader(bool *_stop, QObject *parent) :
    QObject(parent),
    m_currentIndex(0),
    m_webCtrl(new QNetworkAccessManager(this)),
    m_stop(_stop)
{
    connect(m_webCtrl, &QNetworkAccessManager::finished, this, &FileDownloader::fileDownloaded);
}

FileDownloader::~FileDownloader()
{
    delete m_webCtrl;
}

void FileDownloader::downloadAsync(const QStringList &_urls)
{
    m_urls = _urls;

    if(m_urls.size() > 0)
    {
        QNetworkReply* reply = m_webCtrl->get(QNetworkRequest(QUrl(m_urls.at(m_currentIndex))));
        connect(reply, &QNetworkReply::downloadProgress, this, &FileDownloader::downloadProgress);
        connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SIGNAL(downloadError(QNetworkReply::NetworkError)));
    }
}

void FileDownloader::downloadSync(const QStringList &_urls)
{
    m_urls = _urls;

    if(m_urls.size() > 0)
    {
        QNetworkReply* reply = m_webCtrl->get(QNetworkRequest(QUrl(m_urls.at(m_currentIndex))));
        connect(reply, &QNetworkReply::downloadProgress, this, &FileDownloader::downloadProgress);
        connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SIGNAL(downloadError(QNetworkReply::NetworkError)));

        QEventLoop loop;
        connect(this, &FileDownloader::downloadFinished, &loop, &QEventLoop::quit);
        loop.exec();
    }
}

QString FileDownloader::trimFileName(const QString &_sFileName)
{
    return _sFileName.right(_sFileName.length() - _sFileName.lastIndexOf("/") - 1);
}

void FileDownloader::fileDownloaded(QNetworkReply *pReply)
{
    if(m_stop && *m_stop) return;

    QByteArray data = pReply->readAll();
    pReply->deleteLater();
    emit downloaded(trimFileName(m_urls[m_currentIndex]), data, m_currentIndex, m_urls.size());
    m_currentIndex++;

    if(m_currentIndex != m_urls.size())
    {
        QNetworkReply* reply = m_webCtrl->get(QNetworkRequest(QUrl(m_urls.at(m_currentIndex))));
        connect(reply, &QNetworkReply::downloadProgress, this, &FileDownloader::downloadProgress);
        connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SIGNAL(downloadError(QNetworkReply::NetworkError)));
    } else
    {
        emit downloadFinished();
    }
}




