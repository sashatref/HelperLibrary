#pragma once

#include <QObject>
#include <QNetworkReply>
#include <QNetworkAccessManager>

class FileDownloader : public QObject
{
    Q_OBJECT
public:
    FileDownloader(bool *_stop = 0, QObject *parent = 0);
    ~FileDownloader();

    void downloadAsync(const QStringList &_urls);
    void downloadSync(const QStringList &_urls);

    static QString trimFileName(const QString &_sFileName);

signals:
    void downloaded(const QString &_sFileName, const QByteArray &_bData, int _current, int _total);
    void downloadProgress(qint64 _currentBytes, qint64 _totalBytes);
    void downloadError(QNetworkReply::NetworkError);
    void downloadFinished();

private slots:
    void fileDownloaded(QNetworkReply *pReply);

private:
    QNetworkAccessManager *m_webCtrl;
    int m_currentIndex;
    QStringList m_urls;
    bool *m_stop;
};


