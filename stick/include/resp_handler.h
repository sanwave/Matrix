
/*
*
*
*
*	MsgHandler Class Header File		In Matrix
*
*	Created by Bonbon	2015.02.11
*
*	Updated by Bonbon	2015.05.07
*
*/

#ifndef _RESP_HANDLER_H_
#define _RESP_HANDLER_H_

#include "msg_handler.h"

namespace Matrix
{
    class RespHandler :public MsgHandler
    {
    public:
        RespHandler(HttpRequest * request);
        ~RespHandler();

        // parse message from server
        int Parse(const char * msg);
        /*int Handle(void(*req_handler)(MsgHandler*) = NULL);*/
    };
}


#endif
