
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

#ifndef _GET_HANDLER_H_
#define _GET_HANDLER_H_

#include "msg_handler.h"

namespace Matrix
{
    class GetHandler:public MsgHandler
    {
    public:
        GetHandler(HttpRequest * request);
        ~GetHandler();

        // a overloaded version function to handle http get request
        int Handle(void(*req_handler)(MsgHandler*) = NULL);
    };
}


#endif
