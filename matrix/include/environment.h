
/*
*
*
*
*	Environment Class Header File		In Matrix
*
*	Created by Bonbon	2015.01.10
*
*	Updated by Bonbon	2015.01.12
*
*/


#ifndef _ENVIRONMENT_H_
#define _ENVIRONMENT_H_

#include <iostream>
#include "matrix_types.h"

namespace Matrix
{
#ifdef WIN32

#define ANY_SIZE 1

    struct AddrInfo {
        unsigned long	addr;
        unsigned long	mask;
        unsigned long	br_addr;
    };

    struct DynBuf {
        char	*buf;
        int		size;
        DynBuf(int _size = 0) {
            buf = NULL;
            if ((size = _size) > 0) Alloc(size);
        }
        ~DynBuf() {
            free(buf);
        }
        char *Alloc(int _size) {
            if (buf) free(buf);
            buf = NULL;
            if ((size = _size) <= 0) return NULL;
            return	(buf = (char *)malloc(size));
        }
        operator char*() { return (char *)buf; }
        operator unsigned char*() { return (unsigned char *)buf; }
        operator wchar_t*() { return (wchar_t *)buf; }
        operator void*() { return (void *)buf; }
        int		Size() { return size; }
    };

    typedef struct _MIB_IPADDRROW {
        unsigned long          dwAddr;
        unsigned long          dwIndex;
        unsigned long          dwMask;
        unsigned long          dwBCastAddr;
        unsigned long          dwReasmSize;
        unsigned short unused1;
        unsigned short wType;
    } MIB_IPADDRROW, *PMIB_IPADDRROW;

    typedef struct _MIB_IPADDRTABLE {
        unsigned long         dwNumEntries;
        MIB_IPADDRROW table[ANY_SIZE];
    } MIB_IPADDRTABLE, *PMIB_IPADDRTABLE;

#endif

    class Environment
    {
    public:
        // get current dir string, e.g. /usr/local/
        static std::string GetCurrentDir();

#ifdef WIN32
        static AddrInfo * GetIPAddrs(int strict, int *num);
#endif
    };

}

#endif
