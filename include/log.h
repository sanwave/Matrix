
/*
*
*
*
*	Log Class Header File		In Matrix
*
*	Created by Bonbon	2015.01.10
*
*	Updated by Bonbon	2015.01.10
*
*/


#ifndef _LOG_H_
#define _LOG_H_

#include <iostream>
#include <mutex>

#define LOG_ERROR  4
#define LOG_WARN   3
#define LOG_INFO   2
#define LOG_DEBUG  1
#define LOG_TRACE  0

namespace Matrix
{
    class Log
    {
    public:
        static int Write(unsigned char level, std::string info);
        static int Write(unsigned char level, const char * info);

        static std::string GetLevelStr(unsigned char level);
        static unsigned char m_level;

        static std::mutex m_mtx;
    };

}

#endif
