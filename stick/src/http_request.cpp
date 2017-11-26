
/*
*
*
*
*	Http-Request Class Header File		In Matrix
*
*	Created by Bonbon	2015.02.01
*
*	Updated by Bonbon	2015.05.07
*
*/

#include  "http_request.h"

#include <cstdlib>
#include "os.h"
#include "log.h"

#include "convert.h"
#include "string_handler.h"
#include "http_msg.h"


namespace Matrix
{
    HttpRequest::HttpRequest(SOCKET connfd, sockaddr_in * client_addr)
    {
        m_conn = new Socket(connfd);
        m_other_host = new Host();
        m_other_host->SetIp(client_addr->sin_addr.s_addr);
        m_other_host->Port = client_addr->sin_port;
    }
    HttpRequest::HttpRequest(SOCKET connfd, const Host & client)
    {
        m_conn = new Socket(connfd);
        m_other_host = new Host(client);
    }
    HttpRequest::HttpRequest(const HttpRequest & src)
    {
        m_conn = new Socket(src.m_conn->Fd());
        m_other_host = new Host(*(src.m_other_host));
    }
    HttpRequest::~HttpRequest()
    {
        if (NULL != m_conn)
        {
            m_conn->Close();
            delete m_conn;
        }
        if (NULL != m_other_host)
        {
            delete m_other_host;
        }
    }

    int HttpRequest::Send(const char * msg, size_t size, int flags)
    {
        int ret = m_conn->Send(msg, size, flags);
        if (ret < 0)
        {
            Log::Write(LOG_ERROR, "Socket:" + Convert::Int2Str(m_conn->Fd()) + " Send msg failed! ");
            return DO_ERROR;
        }
        Log::Write(LOG_INFO, "Socket:" + Convert::Int2Str(m_conn->Fd()) + " Send msg to " + m_other_host->Addr() + CRLF);
        return DO_SUCCEED;
    }

    int HttpRequest::Receive(HttpMsg * msg, int & size)
    {
        char rx_buf[MAX_TCP_DATA_PAYLOAD] = { 0 };
        size = MAX_TCP_DATA_PAYLOAD;
        int received_length = m_conn->Recv(rx_buf, size, 0);
        if (received_length < 0 && (errno == EINTR || errno == EWOULDBLOCK || errno == EAGAIN))
        {
            received_length = m_conn->Recv(rx_buf, size, 0);
        }
        else if (received_length <= 0)
        {
            Log::Write(LOG_ERROR, "Receive msg error, received_length= " + Convert::Int2Str(received_length));
            return DO_ERROR;
        }

        size_t header_length = strstr(rx_buf, "\r\n\r\n") + 4 - rx_buf;
        if ((int)header_length > size)   //overflow
        {
            Log::Write(LOG_ERROR, "Receive msg bussiness error. Http header is overflow");
            return DO_BUSINESS_ERROR;
        }
        size_t content_length = 0;
        if (NULL != strstr(rx_buf, "Content-Length:"))
        {
            content_length = Convert::Str2Int(StrHandle::BetweenTrim(rx_buf, "Content-Length:", CRLF));
        }
        else if (0 != strncmp(rx_buf, METHOD_GET, 3))
        {
            Log::Write(LOG_ERROR, "Receive msg bussiness error.");
            return DO_BUSINESS_ERROR;       // not currently supported
        }
        char * buff = new char[header_length + content_length + 1];
        memset(buff, 0, header_length + content_length + 1);
        StrHandle::nCopy(buff, rx_buf, received_length);
        msg->RecvMsg = buff;
        msg->HeaderLength = header_length;
        //if (received_length == size || received_length == MAX_TCP_DATA_PAYLOAD)
        {
            char * index = buff;
            int unreceive_length = header_length + content_length - received_length;
            while (unreceive_length > 0 || received_length >= MAX_TCP_DATA_PAYLOAD)
            {
                index += received_length;
                received_length = m_conn->Recv(index, MAX_TCP_DATA_PAYLOAD, 0);
                if (received_length <= 0)
                    break;
                unreceive_length -= received_length;
            }
        }
        Log::Write(LOG_INFO, "Receive req/resp from " + m_other_host->Addr() + CRLF + msg->RecvMsg);

        return DO_SUCCEED;
    }

}
