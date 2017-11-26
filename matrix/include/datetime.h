
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
#include "os_types.h"

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
        static Int64 UnixTime();
        // get millisecond of now time, 0~999
        static Int64 MilliSeconds();

        //get second
        static Int32 Second();
        //get minute
        static Int32 Minute();
        //get hour
        static Int32 Hour();

        //get day of month
        static Int32 Day();
        //get day of week
        static Int32 DayOfWeek();
        //get day of year
        static Int32 DayOfYear();
        //get month
        static Int32 Month();
        //get year
        static Int32 Year();
    };
}

#endif
