
/*
*
*
*
*	Http-Client Class Source File		In Matrix
*
*	Created by Bonbon	2015.01.21
*
*	Updated by Bonbon	2015.05.07
*
*/

#include "http_client.h"

#include "os.h"
#include "log.h"
#include "text_encoder.h"
#include "file.h"

#include "http_msg.h"
#include "environment.h"
#include "http_helper.h"
#include "http_request.h"
#include "resp_handler.h"

namespace Matrix
{
    HttpClient::HttpClient()
        :m_msg_handler(NULL),
        m_full_req_uri(true),
        m_save_as_file(false),
        m_auto_redirect(true) {}

    HttpClient::~HttpClient()
    {
        if (NULL != m_msg_handler)
        {
            delete m_msg_handler;
            m_msg_handler = NULL;
        }
    }

    HttpMsg * HttpClient::Msg()
    {
        if (NULL != m_msg_handler)
        {
            return m_msg_handler->Msg();
        }
        return NULL;
    }

    int HttpClient::Get(const char * url, bool save_as_file)
    {
        m_save_as_file = save_as_file;
        return Request(METHOD_GET, url, NULL);
    }

    int HttpClient::Post(const char * url, const char * request)
    {
        return Request(METHOD_POST, url, request);
    }

    int HttpClient::Request(const char * method, const char * ori_url, const char * body)
    {
        Socket::Init();
        char request_uri[MAX_URL] = { 0 };
        HttpMsg * msg = NULL;
        int size = 0;
        Host host;
        int ret = DO_SUCCEED;
        std::string url = ori_url;

        if (NULL != m_msg_handler)
        {
            delete m_msg_handler;
            m_msg_handler = NULL;
        }

        do
        {
            HttpHelper::ParseUrl(url.c_str(), host, request_uri);

            SOCKET sockfd = ConnectTo(host);
            if (INVALID_SOCKET == sockfd)
            {
                return DO_ERROR;
            }
            HttpRequest * request = new HttpRequest(sockfd, host);
            m_msg_handler = new RespHandler(request);
            msg = m_msg_handler->Msg();
            msg->ReqUri = request_uri;
            std::string req_msg;
            if (m_full_req_uri)
            {
                req_msg = m_msg_handler->MakeReqMsg(host.DomainAddr().c_str(), url.c_str(), method, body);
            }
            else
            {
                req_msg = m_msg_handler->MakeReqMsg(host.DomainAddr().c_str(), request_uri, method, body);
            }

            ret = request->Send(req_msg.c_str(), req_msg.length(), 0);
            if (ret != DO_SUCCEED)
                return ret;

            ret = m_msg_handler->Request()->Receive(msg, size);
            if (ret != DO_SUCCEED)
                return ret;

            ret = m_msg_handler->Parse(msg->RecvMsg);
            if (ret != DO_SUCCEED)
                return ret;

            if (m_save_as_file)
            {
                std::string req_uri = msg->ReqUri;
                std::string filename = req_uri.substr(req_uri.find_last_of('/'));
                if (filename.find_first_of('?') > 0)
                    filename = filename.substr(0, filename.find_first_of('?'));
                filename = Environment::GetCurrentDir() + filename;
                File::OverWrite(TextEncoder(filename).Unicode(), msg->RecvMsg + msg->HeaderLength, msg->ContentLength);
            }

            ret = m_msg_handler->Handle(NULL);
            if (ret != DO_SUCCEED)
                return ret;

            if (m_auto_redirect && !msg->Location.empty()
                && (STATUS_CODE_MOVED_PERMANENTLY == msg->StatusCode || STATUS_CODE_MOVED_TEMPORARILY == msg->StatusCode))
            {
                url = msg->Location;
                continue;
            }
            break;

        } while (1);

        Socket::Uninit();
        return DO_SUCCEED;
    }

    int HttpClient::Request(const std::string& addr, const std::string& req_msg, std::string& resp_msg)
    {
        HttpMsg * msg = NULL;
        int size = 0;
        Host host;
        host.SetAddr(addr.c_str());
        SOCKET sockfd = ConnectTo(host);
        if (INVALID_SOCKET == sockfd)
        {
            return DO_ERROR;
        }
        HttpRequest * request = new HttpRequest(sockfd, host);
        int ret = request->Send(req_msg.c_str(), req_msg.length(), 0);
        if (ret != DO_SUCCEED)
            return ret;

        ret = request->Receive(msg, size);
        if (ret != DO_SUCCEED)
            return ret;
        resp_msg = msg->RecvMsg;
        return ret;
    }

    SOCKET HttpClient::ConnectTo(const Host & server)
    {
        Socket sock;
        int ret = 0;
        ret = sock.Create(AF_INET, SOCK_STREAM, 0);
        if (INVALID_SOCKET == ret)
        {
            return INVALID_SOCKET;
        }
        struct sockaddr_in addr;
        memset(&addr, 0, sizeof(addr));
        addr.sin_family = AF_INET;
        addr.sin_port = htons(server.Port);
        inet_pton(AF_INET, server.Ip.c_str(), &addr.sin_addr);
        ret = sock.Connect((sockaddr *)&addr, sizeof(addr));
        if (ret < 0)
        {
            return INVALID_SOCKET;
        }
        return sock.Fd();
    }
}
