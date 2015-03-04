
/*
*
*
*
*	Udp-Socket Class Source File		In Matrix
*
*	Created by Bonbon	2015.01.12
*
*	Updated by Bonbon	2015.01.12
*
*/

#include "udp_socket.h"

namespace Matrix
{
    UdpSocket::UdpSocket()     {}
    UdpSocket::~UdpSocket()    {}

    int UdpSocket::SendMsg(unsigned long addr, unsigned short port, const char * msg)
    {
        sockaddr_in target;
        target.sin_family = AF_INET;
        target.sin_addr.s_addr = addr;
        target.sin_port = htons(port);

        SendTo(msg, strlen(msg), 0, (sockaddr *)&target, sizeof(target));

        return 0;
    }

    int UdpSocket::SendMsg(const char * addr, unsigned short port, const char * msg)
    {
        sockaddr_in target;
        target.sin_family = AF_INET;
        target.sin_port = htons(port);
        inet_pton(AF_INET, addr, &target.sin_addr);

        SendTo(msg, strlen(msg), 0, (sockaddr *)&target, sizeof(target));

        return 0;
    }
}
