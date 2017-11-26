
/*
*
*
*
*	Hls-Client Class Header File		In Matrix
*
*	Created by Bonbon	2015.01.22
*
*	Updated by Bonbon	2015.05.07
*
*/


#ifndef _HLS_CLIENT_H_
#define _HLS_CLIENT_H_

#include "host.h"

namespace Matrix
{
    class HlsClient
    {
    public:
        HlsClient();
        ~HlsClient();

        // send request to the url
        void ReqContent(const char * url, bool encrypted = false);

    private:
        // add et and token parameter to the uri
        static std::string AddPara(const char * uri);
        // analysis the msg and make response
        int HandleMsg(Host host, const char * msg, char * url);

    private:
        std::string m_req_type;
    };
}

#endif
