
/*
*
*
*
*	OS Class Source File		In Matrix
*
*	Created by Bonbon	2015.01.30
*
*	Updated by Bonbon	2015.01.31
*
*/

#ifndef _OS_H_
#define _OS_H_

#define DO_SUCCEED              1
#define DO_NOTHING              0
#define DO_ERROR               -1
#define DO_BUSINESS_ERROR      -2

namespace Matrix
{
    class OS
    {
    public:
        static void Pause();
        static void Sleep(unsigned int milliseconds);
        static void CleanPtr(void ** ptr);
    };
}

#endif
