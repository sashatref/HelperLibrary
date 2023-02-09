#include "datatransfer.h"
#include "../releaseassert.h"

namespace JsonProtocolNS
{

DataTransfer::DataTransfer(QObject *_parent):
    QObject(_parent)
{

}

DataTransfer::~DataTransfer()
{

}

void DataTransfer::sendDataPacket(const QByteArray &_data, QIODevice *_dest)
{
    qint32 fSize = _data.size();

    _dest->write(reinterpret_cast<const char*>(&fSize), sizeof(fSize));
    _dest->write(_data);
}

void DataTransfer::connectToSocket(QIODevice *_source)
{
    connect(_source, &QIODevice::readyRead, this, &DataTransfer::readyReadSlot);
}

void DataTransfer::readyReadSlot()
{
    QIODevice *socket = qobject_cast<QIODevice*>(sender());
    R_ASSERT(socket)

    int readed = 0;

    if(m_startChank)
    {
        //Если это начало блока, то саначала считываем размер данных
        socket->read(reinterpret_cast<char*>(&m_dataSize), sizeof(m_dataSize));

        //пытаемся сразу читать столько данных, сколько указано в размере
        QByteArray buff = socket->read(m_dataSize);

        //выясняем размер реально считанных данных
        readed = buff.size();

        //сохраняем блок данных
        m_data.append( buff );

        m_startChank = false;
    } else
    {
        //пытаемся читать столько данных, сколько осталось до конца реального размера
        const QByteArray temp = socket->read(m_dataSize - m_data.size());

        //выясняем размер реально считанных данных
        readed = temp.size();

        //сохраняем блок данных
        m_data.append(temp);
    }

    //проверяем, дочитали ли мы все данные текущего пакета до конца
    if(m_data.size() >= m_dataSize)
    {
        //если блок закончен, то испускаем сигнал и обнуляем все переменные
        emit dataParsed(m_data);
        m_data.clear();
        m_dataSize = 0;
        m_startChank = true;

        //если в источнике еще есть данные, то снова запускаем функцию обработки
        if(socket->bytesAvailable() > readed)
        {
            readyReadSlot();
        }
    }
}

}
