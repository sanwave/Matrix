
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
    };
}


#endif

