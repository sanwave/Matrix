
/*
*
*
*
*	Http-Request Class Header File		In Matrix
*
*	Created by Bonbon	2015.02.01
*
*	Updated by Bonbon	2015.05.07
*
*/


#ifndef _HTTP_REQUEST_H_
#define _HTTP_REQUEST_H_

#include <iostream>

#include "host.h"
#include "socket.h"
#include "http_protocol.h"

namespace Matrix
{
    struct HttpMsg;

    class HttpRequest
    {
    public:
        HttpRequest(SOCKET connfd, sockaddr_in * other_host_addr);
        HttpRequest(SOCKET connfd, const Host & other_host);
        HttpRequest(const HttpRequest & src);
        ~HttpRequest();

        // make http message and send request
        int Send(const char * req_body, size_t body_size, int flags);
        // receive messge and save in the *response
        int Receive(HttpMsg *msg, int & size);

    private:
        Socket * m_conn;
        Host * m_other_host;
    };
}

#endif
