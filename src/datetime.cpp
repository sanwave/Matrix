
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

namespace Matrix
{
	std::string DateTime::Now()
	{
		time_t now = time(NULL);
		struct tm *tm_now = localtime(&now);
		char str_time[21];
		strftime(str_time, 21, "%Y-%m-%d %H:%M:%S", tm_now);
		return std::string(str_time);
	}

	int DateTime::Second()
	{
		time_t now = time(NULL);
		struct tm *tm_now = localtime(&now);
		return tm_now->tm_sec;
	}

	int DateTime::Minute()
	{
		time_t now = time(NULL);
		struct tm *tm_now = localtime(&now);
		return tm_now->tm_min;
	}

	int DateTime::Hour()
	{
		time_t now = time(NULL);
		struct tm *tm_now = localtime(&now);
		return tm_now->tm_hour;
	}

	int DateTime::Day()
	{
		time_t now = time(NULL);
		struct tm *tm_now = localtime(&now);
		return tm_now->tm_mday;
	}

	int DateTime::DayOfWeek()
	{
		time_t now = time(NULL);
		struct tm *tm_now = localtime(&now);
		return tm_now->tm_wday;
	}

	int DateTime::DayOfYear()
	{
		time_t now = time(NULL);
		struct tm *tm_now = localtime(&now);
		return tm_now->tm_yday;
	}

	int DateTime::Month()
	{
		time_t now = time(NULL);
		struct tm *tm_now = localtime(&now);
		return tm_now->tm_mon;
	}

	int DateTime::Year()
	{
		time_t now = time(NULL);
		struct tm *tm_now = localtime(&now);
		return tm_now->tm_year;
	}
}
