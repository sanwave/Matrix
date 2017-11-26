
/*
*
*
*
*	Custom-Player-Client Class Source File		In Matrix
*
*	Created by Bonbon	2015.01.22
*
*	Updated by Bonbon	2015.05.07
*
*/

#include "hls_client.h"

#include <sstream>

#include "md5.h"
#include "datetime.h"
#include "http_msg.h"
#include "http_client.h"
#include "http_helper.h"

namespace Matrix
{
    HlsClient::HlsClient() {}
    HlsClient::~HlsClient() {}

    void HlsClient::ReqContent(const char * ori_url, bool encrypted)
    {
        char uri[1024] = { 0 };
        Host server;
        HttpClient http_client;
        std::string url = ori_url;

        if (NULL != strstr(ori_url, "live"))
        {
            m_req_type = "live";
        }

        if (NULL != strstr(ori_url, "TOKEN"))
        {
            encrypted = false;
        }

        do
        {
            HttpHelper::ParseUrl(url.c_str(), server, uri);

            if (encrypted)
            {
                char str[MAX_URL] = { 0 };
                strncpy(str, url.c_str(), url.length());
                std::string url_para = AddPara(uri);
                strncpy(str + url.length(), url_para.c_str(), url_para.length());
                url = str;
            }

            http_client.Get(url.c_str(), true);
            HttpMsg * http_msg = http_client.Msg();
            if (NULL == http_msg)
            {
                break;
            }
            if (STATUS_CODE_OK == http_msg->StatusCode)
            {
                if ("application/octet-stream" == http_msg->ContentType)
                {
                    break;
                }
                char str[REQ_BUF_SIZE] = { 0 };
                HandleMsg(server, http_msg->Body.c_str(), str);
                url = str;
            }
            else
            {
                break;
            }
        } while (1);
    }

    std::string HlsClient::AddPara(const char * uri)
    {
        std::stringstream para;
        if (NULL == strchr(uri, '?'))
        {
            para << "?";
        }
        else
        {
            para << "&";
        }
        para << "ET=" << DateTime::UnixTime() + 9000 << "999";
        para << "&TOKEN=" << MD5(uri + para.str() + "&coship").md5();
        return para.str();
    }

    int HlsClient::HandleMsg(Host host, const char * msg_body, char * url)
    {
        const char * body = msg_body;
        const char * comment = NULL;
        int index = 0;
        while (*(body + index))
        {
            if (NULL == (comment = strchr(body + index, '#')))
            {
                break;
            }
            else if (strchr((body + index), '\n') - comment > 0)
            {
                index = strchr(body + index, '\n') - body + 1;
                continue;
            }
            else
            {
                break;
            }
        }

        const char * end = strchr(body + index, '\n');

        char uri[1024] = { 0 };
        if ("live" == m_req_type)
        {
            strncpy(uri, "/live/", 6);
        }
        else
        {
            strncpy(uri, "/", 1);
        }
        strncpy(uri + strlen(uri), body + index, end - body - index);
        std::string host_addr = host.Addr();

        strncpy(url, "http://", 7);
        strncpy(url + strlen(url), host_addr.c_str(), host_addr.length());
        strncpy(url + strlen(url), uri, strlen(uri));

        return 0;
    }
}
