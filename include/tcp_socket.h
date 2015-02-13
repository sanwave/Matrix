
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
    class TcpConnection :public Socket
    {
    public:
        TcpConnection(SOCKET connfd);
        TcpConnection(const TcpConnection & conn);
        ~TcpConnection();

    private:
        //SOCKET m_connfd;
    };

    class TcpSocket :public Socket
    {
    public:
        TcpSocket();
        TcpSocket(SOCKET connfd);
        TcpSocket(const TcpSocket & src);
        ~TcpSocket();

        SOCKET Accept(struct sockaddr * addr, socklen_t * len);
    };
}

#endif
