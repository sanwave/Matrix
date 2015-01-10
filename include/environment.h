
/*
*
*
*
*	Environment File		In Matrix
*
*	Created by Bonbon	2015.01.10
*
*	Updated by Bonbon	2015.01.10
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
		static char * GetCurrentDir()
		{
			wchar_t dir[MAX_PATH];
			if (::GetModuleFileName(NULL, dir, MAX_PATH))
			{
				wchar_t * separator = wcsrchr(dir, L'\\');
				*++separator = L'\0';
				return Matrix::TextEncoder(dir).Utf8();
			}
			else
			{
				error_log("get current dir failed!");
				return NULL;
			}
		}
	};

}

#endif

