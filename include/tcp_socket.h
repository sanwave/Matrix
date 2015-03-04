
/*
*
*
*
*	Tcp-Socket Class Header File		In Matrix
*
*	Created by Bonbon	2015.01.12
*
*	Updated by Bonbon	2015.01.12
*
*/

#ifndef _TCP_SOCKET_H_
#define _TCP_SOCKET_H_

#include "socket.h"

namespace Matrix
{
    class TcpSocket :public Socket
    {
    public:
        TcpSocket();
        TcpSocket(SOCKET sockfd);
        TcpSocket(const TcpSocket & src);
        ~TcpSocket();
    };
}

#endif
