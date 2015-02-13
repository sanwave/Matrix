
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
#include "convert.h"
#include "datetime.h"
#include "string_handler.h"

namespace Matrix
{
    unsigned char Log::m_level = LOG_DEBUG;

    int Log::Write(unsigned char level, std::string info)
    {
        return Write(level, info.c_str());
    }

    int Log::Write(unsigned char level, const char * info)
    {
        if (level < m_level)
        {
            return DO_NOTHING;
        }
        std::string millistr = Convert::Int2Str(DateTime::MilliSeconds());
        while (millistr.length() < 3)
            millistr = '0' + millistr;
        std::string timestr = DateTime::Now() + "." + millistr;
        std::string levelstr = GetLevelStr(level);
        std::cout << timestr << "    " << levelstr << "    " << info << std::endl;

        int ret = 0;
#ifdef WIN32
        char filename[MAX_PATH] = { 0 };
        ret = ::GetModuleFileNameA(NULL, filename, MAX_PATH);
#else
        char filename[PATH_MAX] = { 0 };
        //ret = readlink("/proc/self/exe", filename, PATH_MAX);
        char cmd[30] = { 0 };
        snprintf(cmd, sizeof(cmd), "/proc/%d/exe", getpid());
        ret = readlink(cmd, filename, PATH_MAX);
#endif
        if (ret > 0 && ret <= sizeof(filename))
        {
#ifdef WIN32
            char * separator = strrchr(filename, '\\');
#else
            char * separator = filename + strlen(filename) - 1;
            if ('/' != *separator)
            {
                *(++separator) = '/';
        }
#endif
            StrHandle::nCopy(separator + 1, "sys.log", 7);
            *(separator + 8) = 0;

            std::fstream file;
            file.open(filename, std::ios_base::app | std::ios_base::binary);
            if (!file.is_open())
            {
                file.close();
                file.open(filename, std::ios_base::out | std::ios_base::binary);
            }
            file.write(timestr.c_str(), timestr.length());
            file.write("    ", 4);
            file.write(levelstr.c_str(), levelstr.length());
            file.write("    ", 4);
            size_t app_size = strlen(info);
            file.write(info, app_size);
            file.write("\r\n", 2);
            file.close();
            return DO_SUCCEED;
    }
        return DO_ERROR;
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

}
