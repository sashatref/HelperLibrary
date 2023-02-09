#pragma once

#include "../export.h"

class HELPERLIBRARY_EXPORT JsonStreamParser : public QObject
{
    Q_OBJECT
public:
    JsonStreamParser(QObject *_parent = nullptr);

signals:
    void objectReceived(const QVariant &_v);

public slots:
    void processData(const QByteArray &_data);

private:
    QByteArray m_recv_buffer;

    QByteArray processBuffer(const QByteArray& buf);
};

