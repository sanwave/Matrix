
/*
*
*
*
*	HttpHelper Class Header File		In Matrix
*
*	Created by Bonbon	2015.02.08
*
*	Updated by Bonbon	2015.02.08
*
*/

#ifndef _HTTP_HELPER_H_
#define _HTTP_HELPER_H_

#include <iostream>
#include "os_types.h"
#include "http_protocol.h"

namespace Matrix
{
    struct IntAndStrPair
    {
        Int32 Key;
        std::string Value;
    };

    static const IntAndStrPair httpStatusCodeAndString[] =
    {
        { STATUS_CODE_CONTINUE,  STATUS_STR_CONTINUE },

        { STATUS_CODE_OK, STATUS_STR_OK },
        { STATUS_CODE_CREATED, STATUS_STR_CREATED },
        { STATUS_CODE_ACCEPTED, STATUS_STR_ACCEPTED },

        { STATUS_CODE_MULTIPLE_CHOICES, STATUS_STR_MULTIPLE_CHOICES },
        { STATUS_CODE_MOVED_PERMANENTLY, STATUS_STR_MOVED_PERMANENTLY },
        { STATUS_CODE_MOVED_TEMPORARILY, STATUS_STR_MOVED_TEMPORARILY },
        { STATUS_CODE_NOT_MODIFIED, STATUS_STR_NOT_MODIFIED },

        { STATUS_CODE_BAD_REQUEST, STATUS_STR_BAD_REQUEST },
        { STATUS_CODE_UNAUTHORIZED, STATUS_STR_UNAUTHORIZED },
        { STATUS_CODE_FORBIDDEN, STATUS_STR_FORBIDDEN },
        { STATUS_CODE_NOT_FOUND, STATUS_STR_NOT_FOUND },
        { STATUS_CODE_METHOD_NOT_ALLOWED, STATUS_STR_METHOD_NOT_ALLOWED },
        { STATUS_CODE_CONFLICT, STATUS_STR_CONFLICT },
        { STATUS_CODE_LENGTH_REQUIRED, STATUS_STR_LENGTH_REQUIRED },
        { STATUS_CODE_REQUEST_ENTITY_TOO_LARGE, STATUS_STR_REQUEST_ENTITY_TOO_LARGE },
        { STATUS_CODE_REQUEST_URI_TOO_LARGE, STATUS_STR_REQUEST_URI_TOO_LARGE },

        { STATUS_CODE_INTERNAL_SERVER_ERROR, STATUS_STR_INTERNAL_SERVER_ERROR },
        { STATUS_CODE_SERVICE_UNAVAILABLE, STATUS_STR_SERVICE_UNAVAILABLE },
        { STATUS_CODE_HTTP_VERSION_NOT_SUPPORTED, STATUS_STR_HTTP_VERSION_NOT_SUPPORTED },
    };

    class Host;
    class HttpHelper
    {
    public:
        // split the url into host addr and request-uri
        static int ParseUrl(const char * url, Host &host, char *uri);
        // return method string of the http request header
        static int GetMethod(const char * header, char *method);
        // return status string to the corresponding status code
        static std::string GetStatusStrbyCode(int code);

        //static int GetCodeByStatusStr(std::string statusStr);
    };
}

#endif
