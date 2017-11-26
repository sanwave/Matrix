
/*
*
*
*
*	RespHandler Class Source File		In Matrix
*
*	Created by Bonbon	2015.02.11
*
*	Updated by Bonbon	2015.05.07
*
*/

#include "resp_handler.h"

#include <iostream>

#include "os.h"
#include "config.h"
#include "convert.h"
#include "string_handler.h"
#include "http_protocol.h"
#include "http_request.h"

namespace Matrix
{
    RespHandler::RespHandler(HttpRequest * request)
        :MsgHandler(request)
    {}

    RespHandler::~RespHandler()
    {}

    int RespHandler::Parse(const char * msg)
    {
        char *head = NULL;
        if (NULL == msg)
        {
            return DO_ERROR;
        }
        const char * index = strstr(msg, "\r\n\r\n");
        if (NULL != index)
        {
            head = new char[Config::RecvHeaderSize];
            memset(head, 0, Config::RecvHeaderSize);

            strncpy(head, msg, index + 4 - msg);
            *(head + (index + 4 - msg)) = 0;

            m_msg->StatusCode = Convert::Str2Int(StrHandle::BetweenTrim(head, " ", " "));
            m_msg->ContentType = StrHandle::BetweenTrim(head, "Content-Type:", CRLF);
            m_msg->Location = StrHandle::BetweenTrim(head, "Location:", CRLF);
            m_msg->ContentLength = Convert::Str2Int(StrHandle::Between(head, "Content-Length:", CRLF));
            m_msg->Header = head;

            if (0 != *(index + 4))
            {
                m_msg->Body = std::string(index + 4);
            }
            delete head;
            return DO_SUCCEED;
        }
        return DO_BUSINESS_ERROR;
    }

    /*int RespHandler::Handle(void(*req_handler)(MsgHandler*))
    {
        return DO_SUCCEED;
    }*/
}
