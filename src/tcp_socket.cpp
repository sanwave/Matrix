
/*
*
*
*
*	Tcp-Socket Class Source File		In Matrix
*
*	Created by Bonbon	2015.01.12
*
*	Updated by Bonbon	2015.01.15
*
*/

#include "tcp_socket.h"

namespace Matrix
{
	TcpConnection::TcpConnection(SOCKET connfd)
		:Socket(connfd)
	{

	}

	TcpConnection::~TcpConnection()
	{

	}

	TcpSocket::TcpSocket()
	{

	}

	TcpSocket::~TcpSocket()
	{

	}

	TcpConnection TcpSocket::Accept(struct sockaddr * addr, int * len)
	{
		SOCKET connfd = Socket::Accept(addr, len);
		TcpConnection conn(connfd);
		return conn;
	}

}
