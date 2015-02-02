
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

	SOCKET Socket::FD()
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
			Log::Write("ERROR", "winsock startup failed\n");
		}
#endif
		return ret;
	}

	int Socket::Create(int family, int type, int protocol)
	{        
		if ((m_sockfd = socket(family, type, protocol)) == INVALID_SOCKET)
		{
			Log::Write("ERROR", "create socket error");
			Close();
			return -1;
		}
        Log::Write("TRACE", "Socket::Create a new socket");
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
			Log::Write("ERROR", "fcntl");
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
        Log::Write("TRACE", "Enter Socket::Bind");
        //std::cout << DateTime::Now().c_str() << " TRACE Test" << std::endl;
		int n;
		struct sockaddr_in addr;
        //std::cout << DateTime::Now().c_str() << " TRACE Before memset" << std::endl;
		memset(&addr, 0, sizeof(addr));
		addr.sin_family = AF_INET;
        //std::cout << DateTime::Now().c_str() << " TRACE Before convert port" << std::endl;;
		addr.sin_port = htons(port);
        //std::cout << DateTime::Now().c_str() << " TRACE Before convert addr" << std::endl;;
        if (INADDR_ANY == (unsigned long)ip || INADDR_LOOPBACK==(unsigned long)ip || INADDR_BROADCAST==(unsigned long)ip)
        {
            addr.sin_addr.s_addr = INADDR_ANY;
        }
        else
        {
            inet_pton(AF_INET, ip, &addr.sin_addr);
        }
        Log::Write("TRACE", "Before Socket::Bind");
        std::cout << DateTime::Now().c_str() << " TRACE Bind IP: " << addr.sin_addr.s_addr << ", Bind Port: " << port << std::endl;
		if ((n = bind(m_sockfd, (struct sockaddr*)&addr, sizeof(addr))) < 0)
		{
			Log::Write("ERROR", "bind socket error");
			Close();
		}
        Log::Write("TRACE", "Exit Socket::Bind");
		return n;
	}

	int Socket::Listen(int backlog)
	{
        Log::Write("TRACE", "Enter Socket::Listen");
		int n;
		if ((n = listen(m_sockfd, backlog)) == -1)
		{
			Log::Write("ERROR", "listen socket error");
			Close();
		}
        Log::Write("TRACE", "Exit Socket::Listen");
		return n;
	}

	SOCKET Socket::Accept(struct sockaddr * addr, socklen_t * len)
	{
        Log::Write("TRACE", "Enter Socket::Accept");
		SOCKET connfd;
		if ((connfd = accept(m_sockfd, addr, len)) == INVALID_SOCKET)
		{
			Log::Write("ERROR", "accept socket error");
			Close();
		}
        Log::Write("TRACE", "Exit Socket::Accept");
		return connfd;
	}

	int Socket::Connect(const struct sockaddr * addr, int len)
	{
		int n;
		if ((n = connect(m_sockfd, addr, len)) < 0)
		{
			Log::Write("ERROR", "connect socket error");
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
