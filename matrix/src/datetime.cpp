
/*
*
*
*
*	DateTime Class Source File		In Matrix
*
*	Created by Bonbon	2015.01.12
*
*	Updated by Bonbon	2015.01.12
*
*/

#include <ctime>
#include "datetime.h"

#ifdef WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#elif __linux__
#endif

namespace Matrix
{
    std::string DateTime::Now()
    {
        time_t now = time(NULL);
        struct tm *tm_now = localtime(&now);
        char str_time[21] = { 0 };
        strftime(str_time, 21, "%Y-%m-%d %H:%M:%S", tm_now);
        return std::string(str_time);
    }

    Int64 DateTime::UnixTime()
    {
#ifdef WIN32
        SYSTEMTIME	st;
        _int64		ft;
        ::GetSystemTime(&st);
        ::SystemTimeToFileTime(&st, (FILETIME *)&ft);
        return	(long)((ft - UNIXTIME_BASE) / 10000000);
#else
        return time(NULL);
#endif
    }

    Int64 DateTime::MilliSeconds()
    {
#ifdef WIN32
        SYSTEMTIME	st;
        _int64		ft;
        ::GetSystemTime(&st);
        ::SystemTimeToFileTime(&st, (FILETIME *)&ft);
        return (((ft - UNIXTIME_BASE) / 10000) % 1000);
#else
        struct timespec xtime;
        clock_gettime(CLOCK_REALTIME, &xtime);
        return (xtime.tv_nsec) / 1000000;
#endif
    }

    Int32 DateTime::Second()
    {
        time_t now = time(NULL);
        struct tm *tm_now = localtime(&now);
        return tm_now->tm_sec;
    }

    Int32 DateTime::Minute()
    {
        time_t now = time(NULL);
        struct tm *tm_now = localtime(&now);
        return tm_now->tm_min;
    }

    Int32 DateTime::Hour()
    {
        time_t now = time(NULL);
        struct tm *tm_now = localtime(&now);
        return tm_now->tm_hour;
    }

    Int32 DateTime::Day()
    {
        time_t now = time(NULL);
        struct tm *tm_now = localtime(&now);
        return tm_now->tm_mday;
    }

    Int32 DateTime::DayOfWeek()
    {
        time_t now = time(NULL);
        struct tm *tm_now = localtime(&now);
        return tm_now->tm_wday;
    }

    Int32 DateTime::DayOfYear()
    {
        time_t now = time(NULL);
        struct tm *tm_now = localtime(&now);
        return tm_now->tm_yday;
    }

    Int32 DateTime::Month()
    {
        time_t now = time(NULL);
        struct tm *tm_now = localtime(&now);
        return tm_now->tm_mon;
    }

    Int32 DateTime::Year()
    {
        time_t now = time(NULL);
        struct tm *tm_now = localtime(&now);
        return tm_now->tm_year;
    }
}
