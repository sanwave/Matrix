
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

#include <cstdlib>
#ifdef WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#else
#include <cstdio>
#include <termios.h>
#include <unistd.h>
#endif

namespace Matrix
{
    void OS::Pause()
    {
#ifdef WIN32
        system("pause");
#else
        printf("Press any key to continue");
        struct termios te;
        int ch;
        tcgetattr(STDIN_FILENO, &te);
        te.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &te);
        tcflush(STDIN_FILENO, TCIFLUSH);
        fgetc(stdin);
        te.c_lflag |= (ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &te);
#endif
    }

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
            delete (*ptr);
            *ptr = NULL;
        }
    }

}
