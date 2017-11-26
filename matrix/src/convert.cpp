
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

#include <string>
#include <sstream>

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
        //return std::to_string((long long int)value);
        return ToStr(value);
    }

    Int32 Convert::Str2Int(std::string value)
    {
        if (value.empty())
        {
            return 0;
        }
        return std::stoi(value);
    }

}
