#pragma once

#include <QObject>
#include <QByteArray>
#include <QIODevice>

#include "../export.h"

/*!
 * \brief The DataReceiver class
 *
 * Данный класс позволяет слушать устройство, в ожидание поступления данных
 * Считывать фрагменты, разбираться где начало и конец пакета и выдавать готовые пакеты данных
 *
 * Для данных, которые передаются в формате [размер всех данных](4 байта) + [данные](n байт)
 * Предназнаенно для передачи данных средних размеров, так как данные складируются в ОЗУ
 * до тех пор, пока не будет найден конец пакета
 */

namespace JsonProtocolNS
{

class HELPERLIBRARY_EXPORT DataTransfer : public QObject
{
    Q_OBJECT
public:
    DataTransfer(QObject *_parent = nullptr);
    ~DataTransfer();

    static void sendDataPacket(const QByteArray &_data, QIODevice *_dest);

public slots:
    void connectToSocket(QIODevice *_source);

signals:
    //готовый пакет данных, который можно парсить
    void dataParsed(const QByteArray &_data);

private slots:
    void readyReadSlot();

private:
    qint32 m_dataSize = 0;
    bool m_startChank = true;
    QByteArray m_data;
};

}

