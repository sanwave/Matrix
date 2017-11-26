
/*
*
*
*
*	Udp-Server Class Source File		In Matrix
*
*	Created by Bonbon	2015.01.13
*
*	Updated by Bonbon	2015.05.07
*
*/
#include "udp_server.h"

#include "os.h"
#include "log.h"
#include "convert.h"

namespace Matrix
{
    UdpServer::UdpServer()
    {
        Socket::Init();
        m_sock.Create(AF_INET, SOCK_DGRAM, 0);
        memset(&m_target, 0, sizeof(m_target));
        bool opt = true;
        //reinterpret_cast<char FAR *>  ==>>  const char * ???
        m_sock.SetOption(SOL_SOCKET, SO_BROADCAST, (const char *)(&opt), sizeof(opt));
    }

    UdpServer::~UdpServer()
    {
        Socket::Uninit();
    }

    int UdpServer::Send(const char * target_ip, unsigned short port, const char * msg, size_t len)
    {
        m_target.sin_family = AF_INET;
        m_target.sin_port = htons(port);
        inet_pton(AF_INET, target_ip, &m_target.sin_addr);

        m_sock.SendTo(msg, len != 0 ? len : strlen(msg), 0, (const sockaddr*)&m_target, sizeof(m_target));
        Log::Write(LOG_INFO, "Send udp msg: to " + std::string(target_ip) + ":" + Convert::Int2Str(port) + "\r\n" + std::string(msg));
        return 0;
    }

    int UdpServer::Listen(int port)
    {
        return m_sock.Bind(INADDR_ANY, port);
    }

    int UdpServer::Run()
    {
        char rx_buf[REQ_BUF_SIZE];
        while (1)
        {
            memset(rx_buf, 0, sizeof(rx_buf));

            int ret = m_sock.RecvFrom(rx_buf, sizeof(rx_buf), 0, NULL, NULL);
            if (-1 == ret)
            {
                Log::Write(LOG_ERROR, "recvfrom error.");
            }
            Log::Write(LOG_INFO, "Received message: " + std::string(rx_buf));
            OS::Sleep(200);
        }
    }
}
