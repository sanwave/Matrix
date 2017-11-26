
/*
*
*
*
*	PostHandler Class Source File		In Matrix
*
*	Created by Bonbon	2015.02.11
*
*	Updated by Bonbon	2015.02.11
*
*/

#include "post_handler.h"

#include <iostream>

#include "os.h"
#include "http_protocol.h"

namespace Matrix
{
    PostHandler::PostHandler(HttpRequest * request)
        :MsgHandler(request)
    {}

    PostHandler::~PostHandler()
    {}

    int PostHandler::Parse(const char * msg)
    {
        ParseHeader(msg);
        const char * index = strstr(msg, "\r\n\r\n");
        if (0 != *(index + 4))
        {
            m_msg->Body = std::string(index + 4);
        }
        return DO_SUCCEED;
    }

    /*int PostHandler::Handle()
    {
        Response(STATUS_CODE_OK, NULL, 0);
        return DO_SUCCEED;
    }*/
}
