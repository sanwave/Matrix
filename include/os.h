
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

#define SIZE_ALL               -1
#define SIZE_ON_HEAP           -2

#define SIGNAL_TASK             1
#define SIGNAL_EXIT             0
#define SIGNAL_EXCEPTION        -1

namespace Matrix
{
    class OS
    {
    public:
        // system("pause")
        static void Pause();
        // system sleep some milliseconds
        static void Sleep(unsigned int milliseconds);
    };
}

#endif
