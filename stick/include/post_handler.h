
/*
*
*
*
*	PostHandler Class Header File		In Matrix
*
*	Created by Bonbon	2015.02.11
*
*	Updated by Bonbon	2015.05.07
*
*/

#ifndef _POST_HANDLER_H_
#define _POST_HANDLER_H_

#include "msg_handler.h"

namespace Matrix
{
    class PostHandler :public MsgHandler
    {
    public:
        PostHandler(HttpRequest * request);
        ~PostHandler();

        int Parse(const char * msg);
        // a overloaded version function to handle http post request
        /*int Handle();*/
    };
}

#endif
