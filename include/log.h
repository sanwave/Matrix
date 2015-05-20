
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
#include <list>
#include <thread>
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
        static void Init();
        static void Uninit();
        static void SetLevel(unsigned char level);
        static std::string GetLevelStr(unsigned char level);
        static void Write(unsigned char level, std::string info);
        static void Write(unsigned char level, const char * info);
        
    private:
        static void WriteLog();

    private:
        static std::mutex m_level_mtx;
        static std::mutex m_log_lines_mtx;
        static std::mutex m_write_log_mtx;
        static unsigned char m_level;
        static std::list<std::string> m_log_lines;
        static std::thread * m_write_log_thread;
    };

}

#endif
