
/*
*
*
*
*	Convert Class Header File		In Matrix
*
*	Created by Bonbon	2015.01.15
*
*	Updated by Bonbon	2015.01.15
*
*/


#ifndef _CONVERT_H_
#define _CONVERT_H_

#include <iostream>
#include <string>
#include <sstream>

namespace Matrix
{
	class Convert
	{
	public:
		template <class T>
		static std::string ToStr(T value);
		static std::string Int2Str(int value);
		static int Str2Int(std::string value);
	};

}

#endif