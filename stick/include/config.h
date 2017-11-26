
/*
*
*
*
*	Config Class Header File		In Matrix
*
*	Created by Bonbon	2015.02.15
*
*	Updated by Bonbon	2015.02.15
*
*/

#ifndef _CONFIG_H_
#define _CONFIG_H_

namespace Matrix
{
    class Config
    {
    public:
        static size_t RecvHeaderSize;
        static size_t RecvBuffSize;
        static size_t SendHeaderSize;
        static size_t SendBuffSize;
        static size_t UrlMaxSize;
    };

    size_t Config::RecvHeaderSize    = 8 * 1024;
    size_t Config::RecvBuffSize      = 8 * 1024;
    size_t Config::SendHeaderSize    = 8 * 1024;
    size_t Config::SendBuffSize      = 8 * 1024;
    size_t Config::UrlMaxSize        = 4 * 1024;
}

#endif
