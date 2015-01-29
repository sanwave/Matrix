
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

#ifdef __linux__
#include <unistd.h>
#endif

#include "text_encoder.h"
#include "file.h"
#include "log.h"

#define ANY_SIZE 1

namespace Matrix
{
#ifdef WIN32
	struct AddrInfo {
		ULONG	addr;
		ULONG	mask;
		ULONG	br_addr;
	};

	struct DynBuf {
		char	*buf;
		int		size;
		DynBuf(int _size = 0)	{
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
		operator char*()	{ return (char *)buf; }
		operator BYTE*()	{ return (BYTE *)buf; }
		operator WCHAR*()	{ return (WCHAR *)buf; }
		operator void*()	{ return (void *)buf; }
		int		Size()		{ return size; }
	};

	typedef struct _MIB_IPADDRROW {
		DWORD          dwAddr;
		DWORD          dwIndex;
		DWORD          dwMask;
		DWORD          dwBCastAddr;
		DWORD          dwReasmSize;
		unsigned short unused1;
		unsigned short wType;
	} MIB_IPADDRROW, *PMIB_IPADDRROW;

	typedef struct _MIB_IPADDRTABLE {
		DWORD         dwNumEntries;
		MIB_IPADDRROW table[ANY_SIZE];
	} MIB_IPADDRTABLE, *PMIB_IPADDRTABLE;

#else
#endif

	class Environment
	{
	public:
		static const char * GetCurrentDir();
#ifdef WIN32
		static AddrInfo * GetIPAddrs(BOOL strict, int *num);
#else
#endif
	};

}

#endif
