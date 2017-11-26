
/*
*
*
*
*	TcpListener Class Source File		In Matrix
*
*	Created by Bonbon	2015.02.08
*
*	Updated by Bonbon	2015.02.08
*
*/

#include "tcp_listener.h"


namespace Matrix
{
    TcpListener::TcpListener()
        :m_sock(NULL)
    {
        Socket::Init();
        m_sock = new Socket();
        m_sock->Create(AF_INET, SOCK_STREAM, 0);
    }

    TcpListener::TcpListener(const TcpListener& src)
        :m_sock(NULL)
    {
        if (NULL != src.m_sock)
        {
   m_sock = new Socket(*src.m_sock);
        }
    }

    TcpListener::~TcpListener()
    {
        if (NULL != m_sock)
        {
   m_sock->Close();
   delete m_sock;
   Socket::Uninit();
        }
    }

    Socket * TcpListener::Sock()
    {
        return m_sock;
    }

    void TcpListener::BindAndListen(int port)
    {
        m_sock->Bind(INADDR_ANY, port);
        m_sock->Listen(1023);
    }

    SOCKET TcpListener::Accept(struct sockaddr * addr)
    {
        socklen_t sin_size = sizeof(*addr);
        return m_sock->Accept(addr, &sin_size);
    }
}
