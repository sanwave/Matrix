
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

        if (NULL == left_pos)
        {
            return "";
        }

        if (NULL != right)
        {
            right_pos = strstr(left_pos + 1, right);
        }

        if (NULL == right_pos)
        {
            //right_pos = source + strlen(source);
            return "";
        }

        size_t len = right_pos - left_pos - strlen(left);
        std::stringstream substr;
        while (len)
        {
            substr << *(right_pos - len--);
        }
        return substr.str();
    }

    std::string StrHandle::Trim(std::string source)
    {
        if (source.empty())
        {
            return source;
        }
        for (int i = 0; source.at(i) == ' '; ++i)
        {
            if (NULL != source.at(i + 1))
            {
                source = source.substr(i + 1);
            }
            else
            {
                return "";
            }
        }
        for (int i = source.length() - 1; i >= 0 && source.at(i) == ' '; --i)
        {
            source = source.substr(0, i - 1);
        }
        return source;
    }

    std::string StrHandle::BetweenTrim(const char * source, const char * left, const char * right)
    {
        //std::string s = Between(source, left, right);
        //std::cout << "        source= "<<source<<" between "<<left<<" and "<<right<<", s=" << s << std::endl;
        return Trim(Between(source, left, right));
    }

    char * StrHandle::nCopy(char * dest, const char * source, size_t size)
    {
        *(dest + size) = 0;
        for (size_t i = 0; i < size; ++i)
        {
            *(dest + i) = *(source + i);
        }
        return dest + size;
    }

    int StrHandle::nCompare(const char * left, const char * right, size_t size)
    {
        for (size_t i = size; i < size; ++i)
        {
            if (*(left + i) != *(right + i))
            {
                return *(left + i) - *(right + i);
            }
        }
        return 0;
    }
}