
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
    TcpConnection::TcpConnection(SOCKET connfd)
        : Socket(connfd)	        {}

    TcpConnection::TcpConnection(const TcpConnection & conn)
        : Socket(conn.FD())         {}

    TcpConnection::~TcpConnection()	{}


    TcpSocket::TcpSocket()	        {}

    TcpSocket::TcpSocket(SOCKET connfd)
        : Socket(connfd)            {}

    TcpSocket::TcpSocket(const TcpSocket & src)
        : Socket(src.FD())          {}

    TcpSocket::~TcpSocket()         {}

    TcpConnection * TcpSocket::Accept(struct sockaddr * addr, socklen_t * len)
    {
        SOCKET connfd = Socket::Accept(addr, len);
        TcpConnection *conn = new TcpConnection(connfd);
        return conn;
    }

}
