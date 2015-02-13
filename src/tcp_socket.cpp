
/*
*
*
*
*	Tcp-Socket Class Source File		In Matrix
*
*	Created by Bonbon	2015.01.12
*
*	Updated by Bonbon	2015.01.15
*
*/

#include "tcp_socket.h"

namespace Matrix
{
    TcpSocket::TcpSocket()	        {}

    TcpSocket::TcpSocket(SOCKET connfd)
        : Socket(connfd)            {}

    TcpSocket::TcpSocket(const TcpSocket & src)
        : Socket(src.FD())          {}

    TcpSocket::~TcpSocket()         {}

    SOCKET TcpSocket::Accept(struct sockaddr * addr, socklen_t * len)
    {
        SOCKET connfd = Socket::Accept(addr, len);
        return connfd;
    }

}
