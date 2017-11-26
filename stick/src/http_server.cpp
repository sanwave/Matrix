
/*
*
*
*
*	HttpServer Class Source File		In Matrix
*
*	Created by Bonbon	2015.01.31
*
*	Updated by Bonbon	2015.05.07
*
*/

#include <thread>
#include "http_server.h"

#include "os.h"
#include "log.h"
#include "tcp_listener.h"
#include "http_request.h"
#include "get_handler.h"
#include "post_handler.h"
#include "http_helper.h"

namespace Matrix
{
    CustomReqHandler HttpServer::m_req_handler = NULL;
    unsigned int HttpServer::m_task_signal = SIGNAL_TASK;
    std::mutex HttpServer::m_task_queue_mtx;
    std::list<Connection*> HttpServer::m_task_queue;
    int HttpServer::m_handler_thread_num = 8;
    std::thread * HttpServer::m_listener_thread = NULL;
    std::list<std::thread *> HttpServer::m_handler_thread_list;

    HttpServer::HttpServer()
    {}

    HttpServer::HttpServer(const HttpServer& src)
    {}

    HttpServer::~HttpServer()
    {}

    void HttpServer::SetHandlerThreadNum(int n)
    {
        if (n > 0)
        {
            m_handler_thread_num = n;
        }
    }

    void HttpServer::SetHandler(CustomReqHandler handler)
    {
        m_req_handler = handler;
    }

    void HttpServer::Init(unsigned short listen_port)
    {
        m_listener_thread = new std::thread(HttpServer::Listen, listen_port);
        for (int i = 0; i < m_handler_thread_num; ++i)
        {
            std::thread * task = new std::thread(HttpServer::Run);
            m_handler_thread_list.push_back(task);
        }
    }

    void HttpServer::Uninit()
    {
        m_task_queue_mtx.lock();
        m_task_signal = SIGNAL_EXIT;
        m_task_queue_mtx.unlock();

        m_listener_thread->join();
        while (m_handler_thread_list.size() > 0)
        {
            std::thread * task = m_handler_thread_list.front();
            task->join();
            m_handler_thread_list.pop_front();
        }
        Log::Write(LOG_INFO, "Destroy HttoServer thread success");
    }

    void HttpServer::Listen(unsigned short port)
    {
        HttpListener *listener = new HttpListener();
        listener->BindAndListen(port);
        // NonBlock Accept with Delay makes Tcp Connection RST Error
        // No Delay makes cpu busy
        //listener->Sock()->SetNonBlock();
        while (true)
        {
            sockaddr_in * client_addr = new sockaddr_in;
            SOCKET connfd = listener->Accept((sockaddr *)client_addr);
            if (INVALID_SOCKET == connfd)
            {
                //OS::Sleep(1);
                continue;
            }
            m_task_queue_mtx.lock();
            switch (m_task_signal)
            {
            case SIGNAL_EXIT:
                delete listener;
                m_task_queue_mtx.unlock();
                return;

            default:
                break;
            }
            m_task_queue.push_back(new Connection(connfd, client_addr));
            m_task_queue_mtx.unlock();
        }
    }

    void HttpServer::Run()
    {
        while (true)
        {
            Connection * conn = NULL;
            while (true)
            {
                m_task_queue_mtx.lock();

                switch (m_task_signal)
                {
                case SIGNAL_EXIT:
                    m_task_queue_mtx.unlock();
                    return;

                default:
                    break;
                }
                if (!m_task_queue.empty())
                {
                    conn = m_task_queue.front();
                    m_task_queue.pop_front();
                    m_task_queue_mtx.unlock();
                    break;
                }

                m_task_queue_mtx.unlock();
                OS::Sleep(1);
            }
            HandleRequest(conn);
            delete conn;
        }
    }

    void HttpServer::HandleRequest(Connection * conn)
    {
        if (NULL == conn)
        {
            return;
        }

        SOCKET connfd = conn->ConnFd;
        sockaddr_in *client_addr_in = conn->ClientAddr;

        MsgHandler *msg_handler = NULL;
        HttpRequest *request = NULL;
        int rx_size = 0;

        request = new HttpRequest(connfd, client_addr_in);
        HttpMsg msg;
        if (DO_SUCCEED == request->Receive(&msg, rx_size))
        {
            char method[8] = { 0 };
            HttpHelper::GetMethod(msg.RecvMsg, method);
            if (METHOD_GET == std::string(method))
            {
                msg_handler = new GetHandler(request);
            }
            else if (METHOD_POST == std::string(method))
            {
                msg_handler = new PostHandler(request);
            }
            else
            {
                // unknown method
                msg_handler = new MsgHandler(request);
            }
            request = NULL;

            msg_handler->Parse(msg.RecvMsg);
            msg_handler->Handle(m_req_handler);
            delete msg_handler;
        }
        else
        {
            delete request;
        }
    }

}
