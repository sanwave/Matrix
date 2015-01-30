
/*
*
*
*
*	OS Class Header File		In Matrix
*
*	Created by Bonbon	2015.01.15
*
*	Updated by Bonbon	2015.01.15
*
*/

#include "os.h"

namespace Matrix
{
    void OS::Sleep(unsigned int milliseconds)
    {
#ifdef WIN32
        ::Sleep(milliseconds);
#else
        struct timeval val;
        val.tv_sec = milliseconds / 1000;
        val.tv_usec = (milliseconds * 1000) % 1 000 000;
        select(0, NULL, NULL, NULL, &val);
#endif
    }

}
