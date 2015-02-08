
/*
*
*
*
*	Udp-Socket Class Header File		In Matrix
*
*	Created by Bonbon	2015.01.13
*
*	Updated by Bonbon	2015.01.13
*
*/

#ifndef _UDP_SOCKET_H_
#define _UDP_SOCKET_H_

#include "socket.h"

namespace Matrix
{
    class UdpSocket : public Socket
    {
    public:
        UdpSocket();
        ~UdpSocket();

        int SendMsg(unsigned long addr, unsigned short port, const char * msg);
        int SendMsg(const char * addr, unsigned short port, const char * msg);
    };
}

#endif