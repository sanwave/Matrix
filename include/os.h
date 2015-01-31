
/*
*
*
*
*	OS Class Source File		In Matrix
*
*	Created by Bonbon	2015.01.15
*
*	Updated by Bonbon	2015.01.15
*
*/

#ifndef _OS_H_
#define _OS_H_

#ifdef WIN32
#include "socket.h" //#include <Windows.h> is confict with socket.h
#else
#include <cstdlib>
#include <unistd.h>
#endif

namespace Matrix
{
    class OS
    {
    public:
        static void Sleep(unsigned int milliseconds);
    };

}

#endif
