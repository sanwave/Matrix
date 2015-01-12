
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

namespace Matrix
{
	class DateTime
	{
	public:

		//get now date and time string
		static std::string Now();

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