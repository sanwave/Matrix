
/*
*
*
*
*	HttpHelper Class Source File		In Matrix
*
*	Created by Bonbon	2015.02.08
*
*	Updated by Bonbon	2015.02.11
*
*/

#include "http_helper.h"

#include <cstring>

#include "os.h"
#include "host.h"
#include "string_handler.h"
#include "http_protocol.h"

namespace Matrix
{
    // http://172.21.10.36:9199/live/cctv.m3u8
    int HttpHelper::ParseUrl(const char * url, Host & host, char * request_url)
    {
        char addr_str[MAX_DOMAIN_NUM] = { 0 };
        const char *host_ptr = NULL;
        const char *port_ptr = NULL;
        const char *root_ptr = NULL;

        host_ptr = strstr(url, "//");
        if (NULL == host_ptr)
        {
            return -1;
        }
        host_ptr += 2;
        root_ptr = strchr(host_ptr, '/');
        if (NULL == root_ptr)
        {
            root_ptr = url + strlen(url);
            strncpy(request_url, "/", 1);
        }
        else
        {
            strncpy(request_url, root_ptr, strlen(root_ptr));
            if (NULL != strchr(request_url, '\r'))
            {
                *strchr(request_url, '\r') = 0;
            }
            if (NULL != strchr(request_url, '\n'))
            {
                *strchr(request_url, '\n') = 0;
            }
        }
        strncpy(addr_str, host_ptr, root_ptr - host_ptr);
        host.SetAddr(addr_str);

        return DO_SUCCEED;
    }

    int HttpHelper::GetMethod(const char * header, char * method)
    {
        const char * seperator = strchr(header, ' ');
        if (NULL != seperator && seperator - header <= 4)
        {
            StrHandle::nCopy(method, header, seperator - header);
            return DO_SUCCEED;
        }
        return DO_BUSINESS_ERROR;
    }

    std::string HttpHelper::GetStatusStrbyCode(int code)
    {
        switch (code)
        {
        case STATUS_CODE_CONTINUE:
            return STATUS_STR_CONTINUE;

        case STATUS_CODE_OK:
            return STATUS_STR_OK;
        case STATUS_CODE_CREATED:
            return STATUS_STR_CREATED;
        case STATUS_CODE_ACCEPTED:
            return STATUS_STR_ACCEPTED;
        case STATUS_CODE_MULTIPLE_CHOICES:
            return STATUS_STR_MULTIPLE_CHOICES;

        case STATUS_CODE_MOVED_PERMANENTLY:
            return STATUS_STR_MOVED_PERMANENTLY;
        case STATUS_CODE_MOVED_TEMPORARILY:
            return STATUS_STR_MOVED_TEMPORARILY;
        case STATUS_CODE_NOT_MODIFIED:
            return STATUS_STR_NOT_MODIFIED;

        case STATUS_CODE_BAD_REQUEST:
            return STATUS_STR_BAD_REQUEST;
        case STATUS_CODE_UNAUTHORIZED:
            return STATUS_STR_UNAUTHORIZED;
        case STATUS_CODE_FORBIDDEN:
            return STATUS_STR_FORBIDDEN;
        case STATUS_CODE_NOT_FOUND:
            return STATUS_STR_NOT_FOUND;
        case STATUS_CODE_METHOD_NOT_ALLOWED:
            return STATUS_STR_METHOD_NOT_ALLOWED;
        case STATUS_CODE_CONFLICT:
            return STATUS_STR_CONFLICT;
        case STATUS_CODE_LENGTH_REQUIRED:
            return STATUS_STR_LENGTH_REQUIRED;
        case STATUS_CODE_REQUEST_ENTITY_TOO_LARGE:
            return STATUS_STR_REQUEST_ENTITY_TOO_LARGE;
        case STATUS_CODE_REQUEST_URI_TOO_LARGE:
            return STATUS_STR_REQUEST_URI_TOO_LARGE;

        case STATUS_CODE_INTERNAL_SERVER_ERROR:
            return  STATUS_STR_INTERNAL_SERVER_ERROR;
        case STATUS_CODE_SERVICE_UNAVAILABLE:
            return STATUS_STR_SERVICE_UNAVAILABLE;
        case STATUS_CODE_HTTP_VERSION_NOT_SUPPORTED:
            return STATUS_STR_HTTP_VERSION_NOT_SUPPORTED;
        default:
            return "";
        }
    }
}
