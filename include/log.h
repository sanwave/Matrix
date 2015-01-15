
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
#include <fstream>
#include "datetime.h"

#ifdef WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#elif __linux__
#endif


namespace Matrix
{
	class Log
	{
	public:
		static int Write(const char * level, const char * info);
	};

}

#endif