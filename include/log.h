
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

//for gcc
#include <cstring>

#ifdef WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#else
#include <unistd.h>
#include <climits>
#endif

#include "datetime.h"
#include "string_handler.h"

namespace Matrix
{
	class Log
	{
	public:
		static int Write(const char * level, const char * info);
	};

}

#endif