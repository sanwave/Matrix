
/*
*
*
*
*	HttpMsg Class Header File		In Matrix
*
*	Created by Bonbon	2015.02.11
*
*	Updated by Bonbon	2015.02.11
*
*/

#ifndef _HTTP_MSG_H_
#define _HTTP_MSG_H_

#include <iostream>
#include <cstring>

namespace Matrix
{
    struct HttpMsg
    {
    public:
        std::string ReqUri;
        std::string Method;
        std::string RequestUri;
        std::string HttpVersion;
        std::string Connection;
        std::string UserAgent;
        size_t HeaderLength;
        size_t ContentLength;
        std::string Host;
        std::string ContentType;
        std::string Location;
        unsigned short StatusCode;
        std::string Header;
        std::string Body;
        char * RecvMsg;

        HttpMsg()
            :RecvMsg(NULL) {}

        HttpMsg(const HttpMsg & msg)
        {
            ReqUri = msg.ReqUri;
            Method = msg.Method;
            RequestUri = msg.RequestUri;
            HttpVersion = msg.HttpVersion;
            Connection = msg.Connection;
            UserAgent = msg.UserAgent;
            HeaderLength = msg.HeaderLength;
            ContentLength = msg.ContentLength;
            Host = msg.Host;
            ContentType = msg.ContentType;
            Location = msg.Location;
            StatusCode = msg.StatusCode;
            Header = msg.Header;
            Body = msg.Body;
            RecvMsg = new char[sizeof(msg.RecvMsg)];
            memcpy(RecvMsg, msg.RecvMsg, sizeof(msg.RecvMsg));
        }

        ~HttpMsg()
        {
            if (NULL != RecvMsg)
            {
                delete RecvMsg;
                RecvMsg = NULL;
            }
        }
    };
}

#endif
