
/*
*
*
*
*	DateTime Class Header File		In Matrix
*
*	Created by Bonbon	2015.01.12
*
*	Updated by Bonbon	2015.01.12
*
*/


#ifndef _DATETIME_H_
#define _DATETIME_H_

#include <iostream>

// 1601年1月1日から1970年1月1日までの通算100ナノ秒
#define UNIXTIME_BASE	((_int64)0x019db1ded53e8000)

namespace Matrix
{
    class DateTime
    {
    public:
        //get now date and time string
        static std::string Now();

        // get unix timestamp (second)
        static time_t UnixTime();
        // get millisecond of now time, 0~999
        static time_t MilliSeconds();

        //get second
        static int Second();
        //get minute
        static int Minute();
        //get hour
        static int Hour();

        //get day of month
        static int Day();
        //get day of week
        static int DayOfWeek();
        //get day of year
        static int DayOfYear();
        //get month
        static int Month();
        //get year
        static int Year();
    };
}

#endif
