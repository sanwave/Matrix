
/*
*
*
*
*	String-Handler Class Header File		In Matrix
*
*	Created by Bonbon	2015.01.23
*
*	Updated by Bonbon	2015.01.23
*
*/

#include "string_handler.h"

namespace Matrix
{
    std::string StrHandle::Between(const char * source, const char * left, const char * right)
    {
        const char * left_pos = strstr(source, left);
        const char * right_pos = strstr(left_pos, right);
        size_t len = right_pos - left_pos - strlen(left);
        std::stringstream substr;
        while (len--)
        {
            substr << *(right_pos - len);
        }
        return substr.str();
    }
}

