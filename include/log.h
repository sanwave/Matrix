
/*
*
*
*
*	Log File		In Matrix
*
*	Created by Bonbon	2015.01.10
*
*	Updated by Bonbon	2015.01.10
*
*/


#ifndef _LOG_H_
#define _LOG_H_

#include <iostream>

namespace Matrix
{

	int error_log(const char * info)
	{
		std::cout << *info << std::endl;
		return 1;
	}

}

#endif