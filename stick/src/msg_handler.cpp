
/*
*
*
*
*	MsgHandler Class Source File		In Matrix
*
*	Created by Bonbon	2015.02.11
*
*	Updated by Bonbon	2015.02.11
*
*/

#include "msg_handler.h"

#include <iostream>
#include <sstream>

#include "os.h"
#include "log.h"
#include "convert.h"
#include "string_handler.h"
#include "http_protocol.h"
#include "http_helper.h"
#include "http_request.h"

namespace Matrix
{
    MsgHandler::MsgHandler(HttpRequest * request)
        :m_msg(NULL),
        m_request(request)
    {
        m_msg = new HttpMsg();
        m_msg->HttpVersion = HTTP_VERSION_11;
        m_msg->UserAgent = USER_AGENT_IE11;
        m_msg->Connection = CONNECTION_CLOSE;
    }

    MsgHandler::MsgHandler(const MsgHandler & src)
    {
        m_msg = new HttpMsg();
        *m_msg = *src.m_msg;
        m_request = new HttpRequest(*src.m_request);
    }

    MsgHandler::~MsgHandler()
    {
        if (NULL != m_request)
        {
            delete m_request;
        }
        if (NULL != m_msg)
        {
            delete m_msg;
        }
    }

    int MsgHandler::Parse(const char * msg)
    {
        return ParseHeader(msg);
    }

    int MsgHandler::ParseHeader(const char * msg)
    {
        m_msg->Header = StrHandle::Between(msg, "", "\r\n\r\n");
        if (m_msg->Header.empty())
        {
            return DO_BUSINESS_ERROR;
        }
        m_msg->Method = StrHandle::BetweenTrim(msg, "", " ");
        m_msg->RequestUri = StrHandle::BetweenTrim(msg, " ", " ");
        m_msg->HttpVersion = StrHandle::BetweenTrim(msg, m_msg->RequestUri.c_str(), CRLF);
        m_msg->Connection = StrHandle::BetweenTrim(msg, "Connection:", CRLF);
        if (NULL != strstr(msg, "Content-Length:"))
        {
            m_msg->ContentLength = Convert::Str2Int(StrHandle::BetweenTrim(msg, "Content-Length:", CRLF));
        }

        return DO_SUCCEED;
    }

    int MsgHandler::Handle(void(*req_handler)(MsgHandler*))
    {
        if (NULL != req_handler)
        {
            req_handler(this);
        }
        //int ret = Response(STATUS_CODE_METHOD_NOT_ALLOWED, NULL, 0);
        return DO_SUCCEED;
    }

    int MsgHandler::Response(int status_code, const char * body, size_t body_size)
    {
        if (NULL == m_request)
        {
            return DO_ERROR;
        }
        std::string header = MakeRespMsg(status_code, body_size);
        m_request->Send(header.c_str(), header.length(), 0);
        if (NULL != body)
        {
            m_request->Send(body, body_size, 0);
        }
        return DO_SUCCEED;
    }

    std::string MsgHandler::MakeReqMsg(const char * host, const char * request_url, const char * method, const char * body)
    {
        std::stringstream msg;
        msg << method << " " << request_url << " " << m_msg->HttpVersion << CRLF;
        msg << "Accept: " << MIME_HTML << ", " << MIME_ANY << CRLF;
        msg << "User-Agent: " << m_msg->UserAgent << CRLF;
        msg << "Host: " << host << CRLF;
        msg << "Connection: " << m_msg->Connection << CRLF;
        msg << "Range: bytes=0-" << CRLF;
        if (0 == strncmp(method, METHOD_POST, strlen(METHOD_POST)))
        {
            msg << "Content-Length: " << strlen(body) << CRLF;
        }
        msg << CRLF;
        if (NULL != body)
        {
            msg << body;
        }
        return msg.str();
    }

    std::string MsgHandler::MakeRespMsg(int status_code, size_t body_size)
    {
        std::stringstream msg;
        msg << m_msg->HttpVersion << " " << status_code << " " << HttpHelper::GetStatusStrbyCode(status_code) << CRLF;
        msg << "Connection: " << (m_msg->Connection.empty() ? "close" : m_msg->Connection) << CRLF;
        if (body_size > 0)
        {
            msg << "Content-Length: " << Convert::Int2Str(body_size) << CRLF;
        }
        if (m_msg->RequestUri.find(".aspx") != std::string::npos ||
            m_msg->RequestUri.find(".htm") != std::string::npos)
        {
            m_msg->ContentType = "text/html; charset=utf-8";
        }
        else if (m_msg->RequestUri.find(".css") != std::string::npos)
        {
            m_msg->ContentType = "text/css";
        }
        else if (m_msg->RequestUri.find(".js") != std::string::npos)
        {
            m_msg->ContentType = "application/x-javascript";
        }
        else if (m_msg->RequestUri.find(".ashx") != std::string::npos)
        {
            m_msg->ContentType = "text/plain; charset=utf-8";
        }
        else if (m_msg->RequestUri.find(".ico") != std::string::npos)
        {
            m_msg->ContentType = "image/x-icon";
        }
        msg << "Content-Type: " << m_msg->ContentType << CRLF;
        msg << "Vary: Accept-Encoding" << CRLF;
        msg << "Date: Mon, 11 May 2015 04:45:26 GMT" << CRLF;
        msg << CRLF;
        return msg.str();
    }

}
