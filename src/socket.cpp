
/*
*
*
*
*	Socket Class Source File		In Matrix
*
*	Created by Bonbon	2015.01.18
*
*	Updated by Bonbon	2015.01.18
*
*/

#include "socket.h"

#include <string>
#include "log.h"
#include "convert.h"

namespace Matrix
{
    Socket::Socket()
        :m_sockfd(INVALID_SOCKET),
        unblocked(false)
    {}

    Socket::Socket(SOCKET sockfd)
        :m_sockfd(sockfd)
    {}

    Socket::~Socket()
    {}

    SOCKET Socket::FD() const
    {
        return m_sockfd;
    }

    int Socket::Init()
    {
        int ret = 0;
#ifdef WIN32
        WSADATA wd;
        ret = WSAStartup(MAKEWORD(2, 0), &wd);
        if (ret < 0)
        {
            Log::Write(LOG_ERROR, "Winsock startup failed");
        }
#endif
        return ret;
    }

    void Socket::Uninit()
    {
#ifdef WIN32
        WSACleanup();
#endif
    }

    int Socket::Create(int family, int type, int protocol)
    {
        if (INVALID_SOCKET == (m_sockfd = socket(family, type, protocol)))
        {
            Log::Write(LOG_ERROR, "Socket::Create error");
            Close();
            return INVALID_SOCKET;
        }
        Log::Write(LOG_TRACE, "Socket::Create a new socket: " + Convert::Int2Str(m_sockfd));
        return m_sockfd;
    }

    int Socket::SetBlock()
    {
        if (!unblocked)
        {
            return 0;
        }
        else
        {
            unblocked = false;
        }
        int ret;
#ifdef WIN32
        u_long arg = 0;
        ret = ioctlsocket(m_sockfd, FIONBIO, &arg);
        if (NO_ERROR != ret)
        {
            Log::Write(LOG_ERROR, "Socket::SetBlock error");
        }
#else
        int cflags = fcntl(m_sockfd, F_GETFL, 0);
        ret = fcntl(m_sockfd, F_SETFL, cflags & ~O_NONBLOCK);
        if (-1 == ret)
        {
            Log::Write(LOG_ERROR, "Socket::SetBlock error");
        }
#endif
        return ret;
    }

    int Socket::SetNonBlock()
    {
        if (unblocked)
        {
            return 0;
        }
        else
        {
            unblocked = true;
        }
        int ret;
#ifdef WIN32
        u_long arg = 1;
        ret = ioctlsocket(m_sockfd, FIONBIO, &arg);
        if (NO_ERROR != ret)
        {
            Log::Write(LOG_ERROR, "Socket::SetNonBlock error");
        }
#else
        int cflags = fcntl(m_sockfd, F_GETFL, 0);
        ret = fcntl(m_sockfd, F_SETFL, cflags | O_NONBLOCK);
        if (-1 == ret)
        {
            Log::Write(LOG_ERROR, "Socket::SetNonBlock error");
        }
#endif
        return ret;
    }

    int Socket::SetOption(int level, int optname, const char * optval, int optlen)
    {
        int n = setsockopt(m_sockfd, level, optname, optval, optlen);
        return n;
    }

    int Socket::Bind(const char * ip, unsigned short port)
    {
        int n;
        struct sockaddr_in addr;
        memset(&addr, 0, sizeof(addr));
        addr.sin_family = AF_INET;
        addr.sin_port = htons(port);
        // it may be a bug
        /*if (INADDR_ANY == (unsigned long)ip || INADDR_LOOPBACK == (unsigned long)ip || INADDR_BROADCAST == (unsigned long)ip)
        {
            addr.sin_addr.s_addr = (unsigned long)ip;
        }
        else
        {
            inet_pton(AF_INET, ip, &addr.sin_addr);
        }*/
        inet_pton(AF_INET, ip, &addr.sin_addr);
        if ((n = bind(m_sockfd, (struct sockaddr*)&addr, sizeof(addr))) < 0)
        {
            Log::Write(LOG_ERROR, "Socket::Bind error");
            Close();
        }
        return n;
    }

    int Socket::Listen(int backlog)
    {
        int n;
        if (-1 == (n = listen(m_sockfd, backlog)))
        {
            Log::Write(LOG_ERROR, "Socket::Listen error");
            Close();
        }
        return n;
    }

    SOCKET Socket::Accept(struct sockaddr * addr, socklen_t * len)
    {
        SOCKET connfd;
        if (INVALID_SOCKET == (connfd = accept(m_sockfd, addr, len)) && !unblocked)
        {
            Log::Write(LOG_ERROR, "Accept socket error");
            Close();
        }
        return connfd;
    }

    int Socket::Connect(const struct sockaddr * addr, int len)
    {
        int n;
        if ((n = connect(m_sockfd, addr, len)) < 0)
        {
            Log::Write(LOG_ERROR, "Connect socket error");
            Close();
        }
        return n;
    }

    int Socket::Send(const char * buff, int len, int flags)
    {
        int n;
        n = send(m_sockfd, buff, len, flags);
        return (n);
    }

    int Socket::Recv(char * buff, int len, int flags)
    {
        int n;
        n = recv(m_sockfd, buff, len, flags);
        return (n);
    }

    int Socket::SendTo(const char * buff, int len, int flags, const sockaddr *to, int tolen)
    {
        int n;
        n = sendto(m_sockfd, buff, len, flags, to, tolen);
        return (n);
    }

    int Socket::RecvFrom(char * buff, int len, int flags, struct sockaddr *from, socklen_t * fromlen)
    {
        int n;
        n = recvfrom(m_sockfd, buff, len, flags, from, fromlen);
        return (n);
    }

    int Socket::Close()
    {
        Log::Write(LOG_TRACE, "Close fd:" + Convert::Int2Str(m_sockfd));
#ifdef WIN32
        return ::closesocket(m_sockfd);
#elif __linux__
        return ::close(m_sockfd);
#endif
    }

}
