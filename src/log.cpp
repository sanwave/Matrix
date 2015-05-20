
/*
*
*
*
*	Log Class Source File		In Matrix
*
*	Created by Bonbon	2015.01.12
*
*	Updated by Bonbon	2015.01.12
*
*/

#include "log.h"

#include <fstream>

//for gcc
#include <cstring>

#ifdef WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#else
#include <unistd.h>
#include <climits>
#endif

#include "os.h"
#include "datetime.h"
#include "string_handler.h"

namespace Matrix
{
    std::mutex Log::m_level_mtx;
    std::mutex Log::m_log_lines_mtx;
    std::mutex Log::m_write_log_mtx;
    unsigned char Log::m_level = LOG_INFO;
    std::list<std::string> Log::m_log_lines;
    std::thread * Log::m_write_log_thread = NULL;

    void Log::Init()
    {
        m_write_log_thread = new std::thread(Log::WriteLog);
    }

    void Log::Uninit()
    {

    }
    
    void Log::SetLevel(unsigned char level)
    {
        m_level_mtx.lock();
        m_level = level;
        m_level_mtx.unlock();
    }

    std::string Log::GetLevelStr(unsigned char level)
    {
        switch (level)
        {
        case LOG_ERROR:
            return "ERROR";

        case LOG_WARN:
            return "WARN";

        case LOG_INFO:
            return "INFO";

        case LOG_DEBUG:
            return "DEBUT";

        case LOG_TRACE:
            return "TRACE";

        default:
            return "";
        }
    }

    void Log::Write(unsigned char level, std::string info)
    {
        Write(level, info.c_str());
    }

    void Log::Write(unsigned char level, const char * info)
    {
        m_level_mtx.lock();
        if (level < m_level)
        {
            m_level_mtx.unlock();
            return;
        }
        m_level_mtx.unlock();

        std::string time;
        std::string millisecond;
        std::string levelstr;
        std::stringstream line;

        std::stringstream convert;
        convert << DateTime::MilliSeconds();

        convert >> millisecond;
        while (millisecond.length() < 3)
            millisecond = '0' + millisecond;

        time = DateTime::Now() + "." + millisecond;
        levelstr = GetLevelStr(level);
        line << time << "    " << levelstr << "    " << info << std::endl;

        m_log_lines_mtx.lock();
        m_log_lines.push_back(line.str());
        m_log_lines_mtx.unlock();
    }

    void Log::WriteLog()
    {
        while (1)
        {
            std::string line;
            while (1)
            {
                m_log_lines_mtx.lock();
                while (!m_log_lines.empty())
                {
                    line += m_log_lines.front();
                    m_log_lines.pop_front();
                }
                m_log_lines_mtx.unlock();

                if (!line.empty())
                {
                    break;
                }
                OS::Sleep(1);
            }

            m_write_log_mtx.lock();
            int ret = 0;
#ifdef WIN32
            char filename[MAX_PATH] = { 0 };
            ret = ::GetModuleFileNameA(NULL, filename, MAX_PATH);
#else
            char filename[PATH_MAX] = { 0 };
            ret = readlink("/proc/self/exe", filename, PATH_MAX);
#endif
            if (ret > 0 && ret <= sizeof(filename))
            {
#ifdef WIN32
                char * separator = strrchr(filename, '\\');
#else
                char * separator = strrchr(filename, '/');
#endif
                StrHandle::nCopy(separator + 1, "sys.log", 7);
                *(separator + 8) = 0;

                std::fstream file;
                file.open(filename, std::ios_base::out | std::ios_base::app | std::ios_base::binary);
                file.write(line.c_str(), line.length());
                file.close();

                std::cout << line;
            }
            m_write_log_mtx.unlock();
        }
    }

}
