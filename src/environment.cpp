
/*
*
*
*
*	Environment Class Source File		In Matrix
*
*	Created by Bonbon	2015.01.10
*
*	Updated by Bonbon	2015.01.12
*
*/


#include "environment.h"

namespace Matrix
{
	char * Environment::GetCurrentDir()
	{
		wchar_t dir[MAX_PATH];
		if (::GetModuleFileName(NULL, dir, MAX_PATH))
		{
			wchar_t * separator = wcsrchr(dir, L'\\');
			*++separator = L'\0';
			return Matrix::TextEncoder(dir).Utf8();
		}
		else
		{
			Log::Write("ERROR", "get current dir failed!");
			return NULL;
		}
	}

	AddrInfo * Environment::GetIPAddrs(BOOL strict, int *num)
	{
		static DWORD(WINAPI *pGetIpAddrTable)(PMIB_IPADDRTABLE, ULONG *, BOOL) = NULL;
		static HMODULE	hMod;

		PMIB_IPADDRTABLE iat = NULL;
		DWORD		dwSize;
		AddrInfo	*ret = NULL;
		int			i, j;
		int			&di = *num;

		di = 0;

		if (!hMod) {
			if (!(hMod = LoadLibrary(L"iphlpapi.dll"))) return NULL;
		}
		if (!pGetIpAddrTable) {
			pGetIpAddrTable = (DWORD(WINAPI *)(PMIB_IPADDRTABLE, ULONG *, BOOL))GetProcAddress(hMod, "GetIpAddrTable");
			if (!pGetIpAddrTable) return NULL;
		}
		if (pGetIpAddrTable(NULL, &dwSize, 0) != ERROR_INSUFFICIENT_BUFFER) return NULL;

		DynBuf	buf(dwSize);
		iat = (PMIB_IPADDRTABLE)(void *)buf;
		if (pGetIpAddrTable(iat, &dwSize, 0) != NO_ERROR || iat->dwNumEntries == 0) return NULL;

		ret = new AddrInfo[iat->dwNumEntries * sizeof(AddrInfo)];

		for (i = 0; i < (int)iat->dwNumEntries; i++) {
			if (iat->table[i].dwAddr == 0x0100007f) continue;
			if (iat->table[i].dwMask == 0xffffffff) continue;
			ret[di].addr = iat->table[i].dwAddr;
			ret[di].mask = iat->table[i].dwMask;
			ret[di].br_addr = (iat->table[i].dwAddr & iat->table[i].dwMask) | ~iat->table[i].dwMask;
			if (strict) {
				for (j = 0; j < di; j++) {
					if (ret[j].br_addr == ret[di].br_addr) break;
				}
				if (j < di) continue;
			}
			di++;
		}

		return	ret;
	}
}


