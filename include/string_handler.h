
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


#ifndef _STRING_HANDLER_H_
#define _STRING_HANDLER_H_

#include <iostream>
#include <string>
#include <sstream>

//for gcc
#include <cstring>

namespace Matrix
{
    class StrHandle
    {
    public:
        // return string value between left and right in string source
        static std::string Between(const char * source, const char * left, const char * right);
        // trim string
        static std::string Trim(std::string source);
        // return trimmed string value between left and right in string source
        static std::string BetweenTrim(const char * source, const char * left, const char * right);
        // copy source value in size character to dest value
        static char * nCopy(char * dest, const char * source, size_t size);
        // compare left value with right value in size character
        static int nCompare(const char * left, const char * right, size_t size);

        // return a lowercase version of the source string
        static std::string ToLower(const char * source) { return ""; }
        // return a uppercase version of the source string
        static std::string ToUpper(const char * source) { return ""; }
        // create string with the format
        static std::string Format(const char * format, const char * args, ...);
    };
}

#endif
