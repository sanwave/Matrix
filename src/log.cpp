
/*
*
*
*
*	Log Class Source File		In Matrix
*
*	Created by Bonbon	2015.01.12
*
*	Updated by Bonbon	2015.01.12
*
*/

#include "log.h"

namespace Matrix
{
	int Log::Write(const char * level, const char * info)
	{
		char filename[MAX_PATH];
		if (::GetModuleFileNameA(NULL, filename, MAX_PATH))
		{
			char * separator = strrchr(filename, '\\');
			strncpy_s(++separator, 9, "sys.log", 7);

			std::fstream file;
			file.open(filename, std::ios_base::app | std::ios_base::binary);
			if (!file.is_open())
			{
				file.close();
				file.open(filename, std::ios_base::out | std::ios_base::binary);
			}
			std::string time = DateTime::Now();
			file.write(time.c_str(), time.length());
			file.write("    ", 4);
			file.write(level, strlen(level));
			file.write("    ", 4);
			size_t app_size = strlen(info);
			file.write(info, app_size);
			file.write("\r\n", 2);
			file.close();
			return 1;
		}
		//std::cout << DateTime::Now().c_str() << "    " 			<< *level << "    " 			<< *info << "    " 			<< std::endl;
		return -1;
	}
}