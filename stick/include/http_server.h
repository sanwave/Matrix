
/*
*
*
*
*	HttpServer Class Header File		In Matrix
*
*	Created by Bonbon	2015.01.12
*
*	Updated by Bonbon	2015.05.07
*
*/


#ifndef _HTTPSERVER_H_
#define _HTTPSERVER_H_

#include <list>
#include <mutex>
#include <cstdio>
#include "socket.h"
#include "http_protocol.h"

#define REQ_HEADER_SIZE 1024

namespace Matrix
{
    class TcpListener;
    typedef TcpListener HttpListener;
    class MsgHandler;
    typedef void(*CustomReqHandler)(MsgHandler *);

    struct Connection
    {
        SOCKET ConnFd;
        sockaddr_in * ClientAddr;

        Connection() {}
        Connection(SOCKET connfd, sockaddr_in * client_addr)
            :ConnFd(connfd), ClientAddr(client_addr) {}

        Connection(const Connection & src)
        {
            ConnFd = src.ConnFd;
            ClientAddr = new sockaddr_in;
            memcpy(ClientAddr, src.ClientAddr, sizeof(sockaddr_in));
        }

        ~Connection()
        {
            if (NULL != ClientAddr)
            {
                delete ClientAddr;
                ClientAddr = NULL;
            }
        }
    };

    class HttpServer
    {
    public:
        HttpServer();
        HttpServer(const HttpServer& src);
        ~HttpServer();

        void Init(unsigned short listen_port);
        void Uninit();
        static void Listen(unsigned short port);
        static void SetHandlerThreadNum(int n);
        static void SetHandler(CustomReqHandler handler);
        static void Run();
        static void HandleRequest(Connection * conn);

    private:
        static CustomReqHandler m_req_handler;
        static unsigned int m_task_signal;
        static std::mutex m_task_queue_mtx;
        static std::list<Connection *> m_task_queue;
        static int m_handler_thread_num;
        static std::thread * m_listener_thread;
        static std::list<std::thread *> m_handler_thread_list;
    };
}

#endif
