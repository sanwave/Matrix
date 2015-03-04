
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
#pragma comment(lib, "Ws2_32")
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

        // return fd value of the socket
        SOCKET FD() const;

        // set socket in block mode
        int SetBlock();
        // set socket in non-block mode
        int SetNonBlock();
        // set socket with the option
        int SetOption(int level, int optname, const char * optval, int optlen);

        // create a new socket
        int Create(int family, int type, int protocol);
        // bind socket to the specified port
        int Bind(const char * ip, unsigned short port);
        // listen on the specified port
        int Listen(int backlog);
        // wait for next connection
        SOCKET Accept(struct sockaddr * addr, socklen_t * len);

        // connect socket to the specified host
        int Connect(const struct sockaddr * addr, int len);

        // send msg
        int Send(const char * buff, int len, int flags);
        // receive msg
        int Recv(char * buff, int len, int flags);
        // send msg to the specified host
        int SendTo(const char * buff, int len, int flags, const sockaddr *to, int tolen);
        // receive msg from the specified host
        int RecvFrom(char * buff, int len, int flags, struct sockaddr *from, socklen_t * fromlen);

        // close socket
        int Close();

        // initialize socket
        static int Init();
        // release socket resource
        static void Uninit();

    private:
        // socket fd
        SOCKET m_sockfd;
    };
}

#endif
