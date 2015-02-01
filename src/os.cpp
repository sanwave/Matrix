
/*
*
*
*
*	OS Class Header File		In Matrix
*
*	Created by Bonbon	2015.01.30
*
*	Updated by Bonbon	2015.01.30
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
        val.tv_usec = (milliseconds * 1000) % 1000000;
        select(0, NULL, NULL, NULL, &val);
#endif
    }

    void OS::CleanPtr(void ** ptr)
    {
        if (NULL != *ptr)
        {
            delete *ptr;
            *ptr = NULL;
        }
    }

}
