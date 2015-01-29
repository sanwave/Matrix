
/*
*
*
*
*	Host Class Header File		In Matrix
*
*	Created by Bonbon	2015.01.19
*
*	Updated by Bonbon	2015.01.19
*
*/


#ifndef _HOST_H_
#define _HOST_H_

#include <iostream>
#include <string>
#include <list>

#include "text_encoder.h"

#ifdef WIN32
#include <Ws2tcpip.h>
#else
#include <arpa/inet.h>
#endif

namespace Matrix
{
	class Host
	{
	public:
		std::string Name;
		std::string User;
		std::string Ip;
		unsigned short Port;

        std::string NickName;

        void SetIp(unsigned long ip);
	};

    class Hosts
    {
    public:
        Hosts();
        ~Hosts();
        int AddHost(Host * host);
        int RemoveHost(Host * host);
        std::list<Host *> GetHostByName(std::string host_name);
        Host *GetHostByAddr(std::string host_addr);
        Host *GetHostByAddr(unsigned long host_addr);

        static Host GetLocalHost();
    private:
        std::list<Host *> m_hosts;
    };

}

#endif
