
/*
*
*
*
*	Environment Class Source File		In Matrix
*
*	Created by Bonbon	2015.01.10
*
*	Updated by Bonbon	2015.01.12
*
*/


#include "environment.h"

namespace Matrix
{
	char * Environment::GetCurrentDir()
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
			Log::Write("ERROR", "get current dir failed!");
			return NULL;
		}
	}
}


