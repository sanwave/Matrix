
/*
*
*
*
*	Socket Class Header File		In Matrix
*
*	Created by Bonbon	2015.01.18
*
*	Updated by Bonbon	2015.01.18
*
*/

#ifndef _SOCKET_H_
#define _SOCKET_H_

#ifdef WIN32
#include <Ws2tcpip.h>
#include <winsock2.h>
#pragma comment(lib,"Ws2_32");
#else
#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>
#define SOCKET int
#define INVALID_SOCKET -1
#endif

//for gcc
#include <cstring>

#define REQ_BUF_SIZE 1024
#define RESP_BUF_SIZE 1024

namespace Matrix
{
    class Socket
    {
    public:

        Socket();

        Socket(SOCKET sockfd);

        ~Socket();

        SOCKET FD();

        int SetBlock();

        int SetNonBlock();

        int SetOption(int level, int optname, const char * optval, int optlen);

        int Create(int family, int type, int protocol);

        int Bind(const char * ip, unsigned short port);

        int Listen(int backlog);

        SOCKET Accept(struct sockaddr * addr, socklen_t * len);

        int Connect(const struct sockaddr * addr, int len);

        int Send(const char * buff, int len, int flags);

        int Recv(char * buff, int len, int flags);

        int SendTo(const char * buff, int len, int flags, const sockaddr *to, int tolen);

        int RecvFrom(char * buff, int len, int flags, struct sockaddr *from, socklen_t * fromlen);

        int Close();

    private:
        int Init();


    private:
        SOCKET m_sockfd;
    };
}

#endif