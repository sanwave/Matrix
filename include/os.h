
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

#ifdef WIN32
#include <Windows.h>
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
