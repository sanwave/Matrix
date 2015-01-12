
/*
*
*
*
*	Environment Class Header File		In Matrix
*
*	Created by Bonbon	2015.01.10
*
*	Updated by Bonbon	2015.01.12
*
*/


#ifndef _ENVIRONMENT_H_
#define _ENVIRONMENT_H_

#include "log.h"
#include "text_encoder.h"


namespace Matrix
{
	class Environment
	{
	public:
		static char * GetCurrentDir();
	};

}

#endif

