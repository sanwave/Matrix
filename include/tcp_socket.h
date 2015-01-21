
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

		~TcpConnection();

	private:
#ifdef WIN32
		SOCKET m_connfd;
#elif _linux_
		int m_connfd;
#endif
	};

	class TcpSocket :public Socket
	{
	public:

		TcpSocket();

		~TcpSocket();

		TcpConnection Accept(struct sockaddr * addr, int * len);

	};
}

#endif
