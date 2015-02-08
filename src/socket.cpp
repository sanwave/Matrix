
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
	{
		Init();
	}

	Socket::Socket(SOCKET sockfd)
	{
		Init();
		m_sockfd = sockfd;
	}

	Socket::~Socket()
	{
#ifdef WIN32
		WSACleanup();
#endif
	}

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
			Log::Write(LOG_ERROR, "Winsock startup failed\n");
		}
#endif
		return ret;
	}

	int Socket::Create(int family, int type, int protocol)
	{
		if ((m_sockfd = socket(family, type, protocol)) == INVALID_SOCKET)
		{
			Log::Write(LOG_ERROR, "Create socket error");
			Close();
			return -1;
		}
        Log::Write(LOG_TRACE, "Socket::Create a new socket: " + Convert::Int2Str(m_sockfd));
		return 0;
	}

	int Socket::SetBlock()
	{
        return 0;
	}

	int Socket::SetNonBlock()
	{
		int ret;
#ifdef WIN32
		u_long arg = 1;
		ret = ioctlsocket(m_sockfd, FIONBIO, &arg);
#else
		if (fcntl(m_sockfd, F_SETFL, O_NONBLOCK))
		{
			Log::Write(LOG_ERROR, "Fcntl error");
			return -1;
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
        if (INADDR_ANY == (unsigned long)ip || INADDR_LOOPBACK==(unsigned long)ip || INADDR_BROADCAST==(unsigned long)ip)
        {
            addr.sin_addr.s_addr = (unsigned long)ip;
        }
        else
        {
            inet_pton(AF_INET, ip, &addr.sin_addr);
        }        
		if ((n = bind(m_sockfd, (struct sockaddr*)&addr, sizeof(addr))) < 0)
		{
			Log::Write(LOG_ERROR, "Bind socket error");
			Close();
		}
        Log::Write(LOG_TRACE, "Socket::Bind port:" + Convert::Int2Str(port));
		return n;
	}

	int Socket::Listen(int backlog)
	{
		int n;
		if ((n = listen(m_sockfd, backlog)) == -1)
		{
			Log::Write(LOG_ERROR, "Listen socket error");
			Close();
		}
        Log::Write(LOG_TRACE, "Socket::Listen start.");
		return n;
	}

	SOCKET Socket::Accept(struct sockaddr * addr, socklen_t * len)
	{
		SOCKET connfd;
		if ((connfd = accept(m_sockfd, addr, len)) == INVALID_SOCKET)
		{
			Log::Write(LOG_ERROR, "Accept socket error");
			Close();
		}
        Log::Write(LOG_TRACE, "Socket::Accept");
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
#ifdef WIN32
		return ::closesocket(m_sockfd);
#elif __linux__
		return ::close(m_sockfd);
#endif
	}

}
