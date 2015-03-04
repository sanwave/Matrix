
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

    TcpSocket::TcpSocket(SOCKET sockfd)
        : Socket(sockfd)            {}

    TcpSocket::TcpSocket(const TcpSocket & src)
        : Socket(src.FD())          {}

    TcpSocket::~TcpSocket()         {}

}
