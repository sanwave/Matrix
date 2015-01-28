
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
#include <sstream>

namespace Matrix
{
    class StrHandle
    {
    public:
        //StrHandle();
        static std::string Between(const char * source, const char * left, const char * right);
        static std::string Trim(std::string source);
        static std::string BetweenTrim(const char * source, const char * left, const char * right);
        static char * nCopy(char * dest, const char * source, size_t size);
    };
}


#endif

