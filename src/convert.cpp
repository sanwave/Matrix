
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
#ifdef WIN32
		return std::to_string(value).c_str();
#else
        return ToStr(value);
#endif
	}

	int Convert::Str2Int(std::string value)
	{
#ifdef WIN32
		return std::stoi(value);
#else
        std::stringstream s;
        int result = 0;
        s << value;
        s >> result;
        return result;
#endif
	}

}