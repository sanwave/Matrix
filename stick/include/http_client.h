
/*
*
*
*
*	Http-Client Class Header File		In Matrix
*
*	Created by Bonbon	2015.01.21
*
*	Updated by Bonbon	2015.05.07
*
*/


#ifndef _HTTP_CLIENT_H_
#define _HTTP_CLIENT_H_

#include <iostream>

#include "host.h"
#include "socket.h"
#include "http_protocol.h"

#define MAX_URL 1024

namespace Matrix
{
    class HttpMsg;
    class MsgHandler;

    class HttpClient
    {
    public:
        HttpClient();
        ~HttpClient();

        HttpMsg * Msg();

        // send http get request
        int Get(const char * url, bool save_file = false);

        // send http post request
        int Post(const char * url, const char * request);

        int Request(const std::string& addr, const std::string& req_msg, std::string& resp_msg);

    private:
        // connect to the host
        static SOCKET ConnectTo(const Host &server);

        // send request(http message) to the connected host
        int Request(const char * method, const char * url, const char * body);

    private:
        MsgHandler * m_msg_handler;
        bool m_full_req_uri;
        bool m_save_as_file;
        bool m_auto_redirect;
    };
}

#endif
