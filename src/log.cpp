
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

namespace Matrix
{
    int Log::Write(const char * level, const char * info)
    {
        int ret = 0;
#ifdef WIN32
        char filename[MAX_PATH];
        ret = ::GetModuleFileNameA(NULL, filename, MAX_PATH);
#else
        char filename[PATH_MAX];
        ret = readlink("/proc/self/exe", filename, PATH_MAX);
#endif
        if (ret > 0 && ret <= sizeof(filename))
        {
            char * separator = strrchr(filename, '\\');
            StrHandle::nCopy(++separator, "sys.log", 7);

            std::fstream file;
            file.open(filename, std::ios_base::app | std::ios_base::binary);
            if (!file.is_open())
            {
                file.close();
                file.open(filename, std::ios_base::out | std::ios_base::binary);
            }
            std::string time = DateTime::Now();
            file.write(time.c_str(), time.length());
            file.write("    ", 4);
            file.write(level, strlen(level));
            file.write("    ", 4);
            size_t app_size = strlen(info);
            file.write(info, app_size);
            file.write("\r\n", 2);
            file.close();
            return 1;
        }
        return -1;
    }
}