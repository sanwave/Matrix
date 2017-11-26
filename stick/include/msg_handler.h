
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

#ifndef _MSG_HANDLER_H_
#define _MSG_HANDLER_H_

#include "http_msg.h"

namespace Matrix
{
    class Host;
    class HttpRequest;
    class MsgHandler
    {
    public:
        MsgHandler(HttpRequest * request);
        MsgHandler(const MsgHandler & src);
        virtual ~MsgHandler();

        HttpMsg * Msg() { return m_msg; }

        HttpRequest * Request()
        {
   return m_request;
        }

        // parse message from client
        virtual int Parse(const char * msg);

        // parse header of msg from client
        int ParseHeader(const char * msg);

        // handle message from client
        virtual int Handle(void(*req_handler)(MsgHandler*));

        // response to the other host
        int Response(int status_code, const char * body, size_t body_size);

        // client ==>> server
        std::string MakeReqMsg(const char * host, const char * request_url, const char * method, const char * body);

        // server ==>> client
        std::string MakeRespMsg(int status_code, size_t body_size);

    protected:
        HttpMsg * m_msg;
        HttpRequest * m_request;
    };
}


#endif
