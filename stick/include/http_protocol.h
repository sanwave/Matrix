
/*
*
*
*
*	Http-Protocol Class Header File		In Matrix
*
*	Created by Bonbon	2015.01.29
*
*	Updated by Bonbon	2015.01.29
*
*/


#ifndef _HTTP_PROTOCOL_H_
#define _HTTP_PROTOCOL_H_


#define METHOD_GET                 "GET"
#define METHOD_POST                "POST"
#define METHOD_HEAD                "HEAD"

#define HTTP_VERSION_10            "HTTP/1.0"
#define HTTP_VERSION_11            "HTTP/1.1"

#define CRLF                       "\r\n"

#define CONNECTION_KEEP_ALIVE      "Keep-Alive"
#define CONNECTION_CLOSE           "close"

#define MIME_HTML                  "text/html"
#define MIME_BINARY                "application/octet-stream"
#define MIME_ANY                   "*/*"

#define USER_AGENT_IE11            "Mozilla/5.0 (Windows NT 6.1; WOW64; Trident/7.0; rv:11.0) like Gecko"
#define USER_AGENT_CHROME          "Mozilla/5.0 (Windows NT 6.1; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/39.0.2171.99 Safari/537"

#define SERVER_IIS                 "Microsoft-IIS/7.5"


#define STATUS_CODE_CONTINUE                    100

#define STATUS_CODE_OK                          200
#define STATUS_CODE_CREATED                     201
#define STATUS_CODE_ACCEPTED                    202

#define STATUS_CODE_MULTIPLE_CHOICES            300
#define STATUS_CODE_MOVED_PERMANENTLY           301
#define STATUS_CODE_MOVED_TEMPORARILY           302
#define STATUS_CODE_NOT_MODIFIED                304

#define STATUS_CODE_BAD_REQUEST                 400
#define STATUS_CODE_UNAUTHORIZED                401
#define STATUS_CODE_FORBIDDEN                   403
#define STATUS_CODE_NOT_FOUND                   404
#define STATUS_CODE_METHOD_NOT_ALLOWED          405
#define STATUS_CODE_CONFLICT                    409
#define STATUS_CODE_LENGTH_REQUIRED             411
#define STATUS_CODE_REQUEST_ENTITY_TOO_LARGE    413
#define STATUS_CODE_REQUEST_URI_TOO_LARGE       414

#define STATUS_CODE_INTERNAL_SERVER_ERROR       500
#define STATUS_CODE_SERVICE_UNAVAILABLE         503
#define STATUS_CODE_HTTP_VERSION_NOT_SUPPORTED  505


#define STATUS_STR_CONTINUE                     "Continue"

#define STATUS_STR_OK                           "OK"
#define STATUS_STR_CREATED                      "Created"
#define STATUS_STR_ACCEPTED                     "Accepted"

#define STATUS_STR_MULTIPLE_CHOICES             "Multiple Choices"
#define STATUS_STR_MOVED_PERMANENTLY            "Moved Permanently"
#define STATUS_STR_MOVED_TEMPORARILY            "Moved Temporarily"
#define STATUS_STR_NOT_MODIFIED                 "Not Modified"

#define STATUS_STR_BAD_REQUEST                  "Bad Request"
#define STATUS_STR_UNAUTHORIZED                 "Unauthorized"
#define STATUS_STR_FORBIDDEN                    "Forbidden"
#define STATUS_STR_NOT_FOUND                    "Not Found"
#define STATUS_STR_METHOD_NOT_ALLOWED           "Method Not Allowed"
#define STATUS_STR_CONFLICT                     "Conflict"
#define STATUS_STR_LENGTH_REQUIRED              "Length Required"
#define STATUS_STR_REQUEST_ENTITY_TOO_LARGE     "Request Entity Too Large"
#define STATUS_STR_REQUEST_URI_TOO_LARGE        "Request-URI Too Large"

#define STATUS_STR_INTERNAL_SERVER_ERROR        "Internal Server Error"
#define STATUS_STR_SERVICE_UNAVAILABLE          "Service Unavailable"
#define STATUS_STR_HTTP_VERSION_NOT_SUPPORTED   "HTTP Version not supported"


#endif
