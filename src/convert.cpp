
/*
*
*
*
*	Convert Class Source File		In Matrix
*
*	Created by Bonbon	2015.01.15
*
*	Updated by Bonbon	2015.01.15
*
*/

#include "convert.h"

namespace Matrix
{
	template <class T>
	std::string Convert::ToStr(T value)
	{
		std::stringstream strvalue;
		strvalue << value;
		return strvalue.str();
	}

	std::string Convert::Int2Str(int value)
	{
		return std::to_string(value).c_str();
	}

	int Convert::Str2Int(std::string value)
	{
		return std::stoi(value);
	}

}