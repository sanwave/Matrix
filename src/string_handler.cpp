
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
        for (size_t i = 0; i < source.length() && source.at(i) == ' '; ++i)
        {
            source = source.substr(i + 1);
        }
        if (0 == source.length())
        {
            return "";
        }
        for (size_t i = source.length() - 1; i >= 0 && source.at(i) == ' '; --i)
        {
            source = source.substr(0, i);
        }
        return source;
    }

    std::string StrHandle::BetweenTrim(const char * source, const char * left, const char * right)
    {
        std::string str = Between(source, left, right);
        return Trim(str);
    }

    // only copy size character
    char * StrHandle::nCopy(char * dest, const char * source, size_t size)
    {
        //*(dest + size) = 0;
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

    std::string StrHandle::Format(const char * format, const char * args, ...)
    {
        std::stringstream stream;
        while (*format)
        {
            if ('{' != *format)
            {
                stream << *format;
                ++format;
            }
            else if ('{' == *(format + 1))
            {
                stream << '{';
                format += 2;
            }
            else if ('{' != *(format + 1) && NULL != strchr(format, '}'))
            {
                std::string index = BetweenTrim(format, "{", "}");
                stream << *(&args + stoi(index));
                format = strchr(format, '}') + 1;
            }
            else
            {
                return "";
            }
        }
        return stream.str();
    }

    std::string & StrHandle::ReplaceAll(std::string & str, const std::string & old_value, const std::string & new_value)
    {
        if (old_value == new_value)
        {
            return str;
        }
        
        std::string::size_type pos(0);
        while (true)
        {
            if (std::string::npos != (pos = str.find(old_value, pos + new_value.length())))
            {
                str.replace(pos, old_value.length(), new_value);
            }
            else
            {
                break;
            }
        }
        return str;
    }
}
