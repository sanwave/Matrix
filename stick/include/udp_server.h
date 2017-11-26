
/*
*
*
*
*	Udp-Server Class Header File		In Matrix
*
*	Created by Bonbon	2015.01.13
*
*	Updated by Bonbon	2015.01.13
*
*/

#ifndef _UDP_SERVER_H_
#define _UDP_SERVER_H_

#include "socket.h"

namespace Matrix
{
    class UdpServer
    {
    public:
        // create and initialize udp socket
        UdpServer();
        ~UdpServer();

        // send message to target addr
        int Send(const char * ip, unsigned short port, const char * msg, size_t len = 0);
        // listen on the specified port
        int Listen(int port);
        int Run();

    private:
        Socket m_sock;
        sockaddr_in m_target;
    };
}

#endif
