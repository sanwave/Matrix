
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
        static std::string Between(const char * source, const char * left, const char * right);
        static std::string Trim(std::string source);
        static std::string BetweenTrim(const char * source, const char * left, const char * right);
        static char * nCopy(char * dest, const char * source, size_t size);
        static int nCompare(const char * left, const char * right, size_t size);
        static std::string ToLower(const char * source) { return ""; }
        static std::string ToUpper(const char * source) { return ""; }
        static std::string Format(const char * format, const char * args, ...);
    };
}

#endif
