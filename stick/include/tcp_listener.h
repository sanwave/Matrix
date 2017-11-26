
/*
*
*
*
*	TcpListener Class Header File		In Matrix
*
*	Created by Bonbon	2015.02.08
*
*	Updated by Bonbon	2015.02.08
*
*/

#ifndef _TCP_LISTENER_H_
#define _TCP_LISTENER_H_

#include "socket.h"

namespace Matrix
{
    class TcpListener
    {
    public:
        // init socket and create socket
        TcpListener();
        TcpListener(const TcpListener& src);
        ~TcpListener();

        // return socket class pointer
        Socket * Sock();
        // bind socket to the specified port and listen on the port
        void BindAndListen(int port);
        // wait for new connection
        SOCKET Accept(struct sockaddr * addr);

    private:
        Socket * m_sock;
    };
}

#endif
