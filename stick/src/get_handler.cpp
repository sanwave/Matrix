
/*
*
*
*
*	MsgHandler Class Source File		In Matrix
*
*	Created by Bonbon	2015.02.11
*
*	Updated by Bonbon	2015.05.07
*
*/

#include "get_handler.h"

#include <iostream>

#include "os.h"
#include "file.h"
#include "environment.h"
#include "http_protocol.h"

namespace Matrix
{
    GetHandler::GetHandler(HttpRequest * request)
        :MsgHandler(request) {}
    GetHandler::~GetHandler() {}

    int GetHandler::Handle(void(*req_handler)(MsgHandler*))
    {
        std::string current_dir = Environment::GetCurrentDir();
        std::string uri = current_dir + m_msg->RequestUri;

        if (File::Exist(uri.c_str()))
        {
            char * content = File(uri.data()).Binary(-1);
            size_t file_size = File::GetSize(uri.data());
            Response(STATUS_CODE_OK, content, file_size);
            delete content;
        }
        else
        {
            Response(STATUS_CODE_NOT_FOUND, NULL, 0);
        }
        return DO_SUCCEED;
    }
}
