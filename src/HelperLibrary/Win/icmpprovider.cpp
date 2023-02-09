#include "icmpprovider.h"
#include "winapiqt.h"
#include "../Exceptions/userexception.h"
#include "../functions.h"

#include <icmpapi.h>

namespace HelperLibraryNS
{

static const bool GetIpListFromHostname(const QString &chHost, QStringList &IpList) {
    WSADATA wsaData;

    int i = 0;
    struct in_addr addr;

    // Initialize Winsock
    const int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0)
    {
        qDebug() << "WSAStartup failed: " << iResult;
        return false;
    }

    struct hostent *remoteHost;
    remoteHost = gethostbyname(chHost.toStdString().c_str());
    const DWORD dwError = WSAGetLastError();

    if (WSACleanup() != 0) {
        qDebug() << "Failed to clear windows sockets";
    }

    if (remoteHost == NULL) {
        if (dwError != 0) {
            if (dwError == WSAHOST_NOT_FOUND)
            {
                qDebug() << "Host not found";
                return false;
            }
            else if (dwError == WSANO_DATA)
            {
                qDebug() << "No data record found";
                return false;
            }
            else
            {
                qDebug() << "Function failed with error: " << dwError;
                return false;
            }
        }
    }
    else {
        //qDebug() << "Function returned:";
        //qDebug() << "Official name: " << remoteHost->h_name;
        for (char**pAlias = remoteHost->h_aliases; *pAlias != 0; pAlias++)
        {
            qDebug() << "Alternate name #" << ++i << ": " << *pAlias;
        }
        //qDebug() << "Address type: ";
        switch(remoteHost->h_addrtype) {
        case AF_INET:
            //qDebug() << "AF_INET\n";
            break;
        case AF_NETBIOS:
            //qDebug() << "AF_NETBIOS\n";
            break;
        default:
            //qDebug() << "Unknown type: " << remoteHost->h_addrtype;
            break;
        }
        //qDebug() << "Address length: " << remoteHost->h_length;

        i = 0;
        if (remoteHost->h_addrtype == AF_INET) {
            while (remoteHost->h_addr_list[i] != 0) {
                addr.s_addr = *(u_long*)remoteHost->h_addr_list[i++];
                const char *chAddr = inet_ntoa(addr);
                IpList << chAddr;
                //qDebug() << "\tIP Address #" <<  i << " | " <<  chAddr;
            }
        }
        else if (remoteHost->h_addrtype == AF_NETBIOS) {
            //qDebug() << "NETBIOS address was returned";
        }
    }
    // если хот¤ бы один ip-адрес существует
    return IpList.size();
}

static unsigned long GetNetAddress(const char *chHostOrIp) {
    WSADATA wsaData;
    // Initialize Winsock
    const int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {

        return INADDR_NONE;
    }

    unsigned long ipaddr = inet_addr(chHostOrIp);
    if (ipaddr == INADDR_NONE) {
        QStringList AIpList;
        if (GetIpListFromHostname(chHostOrIp, AIpList))
        {
            // пока тестово по первому ip-шнику, а там посмотрим
            for (int i = 0; i < AIpList.size(); i++)
            {
                const QString sHost(AIpList.at(i).trimmed());

                ipaddr = inet_addr(sHost.toStdString().c_str());

                if (ipaddr != INADDR_NONE)
                {
                    break;
                }
            }
        }
    }

    if (WSACleanup() != 0) {
        qDebug() << "Failed to clear windows sockets";
    }

    return ipaddr;
}

IcmpProvider::IcmpProvider():
    m_ptr(IcmpCreateFile())
{

}

IcmpProvider::~IcmpProvider()
{

}

bool IcmpProvider::ping(const QString &_addr, int timeout)
{
    using HelperLibrary::UserExceptions::BaseException;

    unsigned long ipaddr = INADDR_NONE;

    QString currIP;

//    QHostInfo hostInfo = QHostInfo::fromName(_addr);
//    if(hostInfo.addresses().size())
//    {
//        for(const QHostAddress &a : hostInfo.addresses())
//        {
//            if(a.protocol() == QAbstractSocket::IPv4Protocol)
//            {
//                currIP = a.toString();
//                ipaddr = inet_addr(a.toString().toStdString().c_str());
//            }
//        }
//    }

    ipaddr = GetNetAddress(_addr.toStdString().c_str());

    qDebug() << QString("Try ping host [%1]").arg(currIP);

    if(ipaddr == INADDR_NONE)
    {
        throw BaseException(QString("IcmpProvider::ping | Can't resolve real IP-address for [%1]").arg(_addr), false);
    }

    char sendData[32] = "Data Buffer";      // Буффер отсылаемых данных

    QByteArray outBuffer;
    int replySize = sizeof(ICMP_ECHO_REPLY) + sizeof(sendData);
    outBuffer.resize(replySize);



    int retVal = IcmpSendEcho(m_ptr.get(), ipaddr, sendData, sizeof(sendData),
                              NULL, outBuffer.data(), replySize, timeout);

    if(retVal == 0)
    {
        throw BaseException("IcmpProvider::ping | " + WinApiQt::getLastErrorMsg(), false);
    }

    PICMP_ECHO_REPLY pEchoReply = (PICMP_ECHO_REPLY)outBuffer.data();

    switch (pEchoReply->Status)
    {
    case IP_SUCCESS:
        return true;
        break;
    case IP_DEST_HOST_UNREACHABLE:
        throw BaseException("IcmpProvider::ping | Destination host was unreachable", false);
        break;
    case IP_DEST_NET_UNREACHABLE:
        throw BaseException("IcmpProvider::ping | Destination Network was unreachable", false);
        break;
    case IP_REQ_TIMED_OUT:
        throw BaseException("IcmpProvider::ping | Request timed out", false);
        break;
    default:
        throw BaseException("IcmpProvider::ping | Unknown status!", false);
        break;
    }

    return true;
}

bool IcmpProvider::pingAddr(const QString &_addr, int timeout)
{
    IcmpProvider prov;
    return prov.ping(_addr, timeout);
}


}
