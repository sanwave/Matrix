
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

        const char * left_pos = source;
        const char * right_pos = source + strlen(source);

        if (NULL != left)
        {
            left_pos = strstr(source, left);
        }

        if (NULL != left_pos)
        {
            right_pos = strstr(left_pos, right);
        }
        else
        {
            return "";
        }

        if (NULL == right_pos)
        {
            //right_pos = source + strlen(source);
            return "";
        }
            
        size_t len = right_pos - left_pos - strlen(left);
        std::stringstream substr;
        while (len--)
        {
            substr << *(right_pos - len);
        }
        return substr.str();
    }

    std::string StrHandle::Trim(std::string source)
    {
        if (source.empty())
        {
            return source;
        }
        for (int i = 0; source.at(i) != ' '; ++i)
        {
            source = source.substr(i);
        }
        for (int i = source.length(); source.at(i) != ' '; --i)
        {
            source = source.substr(0, i);
        }
        return source;
    }

    std::string StrHandle::BetweenTrim(const char * source, const char * left, const char * right)
    {
        return Trim(Between(source, left, right));
    }
}

