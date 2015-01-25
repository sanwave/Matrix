
/*
*
*
*
*	Host Class Header File		In Matrix
*
*	Created by Bonbon	2015.01.19
*
*	Updated by Bonbon	2015.01.24
*
*/

#include "host.h"

namespace Matrix
{
    void Host::SetIp(unsigned long ip)
    {
        char addr[256];
        in_addr s;
        s.s_addr = ip;
        inet_ntop(AF_INET, (void *)&s, addr, sizeof(addr));
        Ip = addr;
    }

    Hosts::Hosts()
    {
        m_hosts.clear();
    }
    Hosts::~Hosts()
    {
        while (!m_hosts.empty())
        {
            delete m_hosts.front();
            m_hosts.pop_front();
        }
    }

    int Hosts::AddHost(Host * host)
    {
        if (NULL == GetHostByAddr(host->Ip))
        {
            m_hosts.push_back(host);
            return 1;
        }
        return 0;
    }

    int Hosts::RemoveHost(Host * host)
    {
        if (NULL != host)
        {
            m_hosts.remove(host);
            delete host;
            host = NULL;
            return 1;
        }
        return 0;
    }

    std::list<Host *> Hosts::GetHostByName(std::string host_name)
    {
        std::list<Host *> hosts;
        std::list<Host *>::const_iterator iter;
        for (iter = m_hosts.begin(); iter!=m_hosts.end(); ++iter)
        {
            if (host_name == (*iter)->Name)
            {
                hosts.push_back(*iter);
            }
        }
        return hosts;
    }

    Host * Hosts::GetHostByAddr(std::string host_addr)
    {
        std::list<Host *>::const_iterator iter;
        for (iter = m_hosts.begin(); iter != m_hosts.end(); ++iter)
        {
            if (host_addr == (*iter)->Ip)
            {
                return (*iter);
            }
        }
        return NULL;
    }

    Host * Hosts::GetHostByAddr(unsigned long host_addr)
    {
        Host host;
        host.SetIp(host_addr);
        return GetHostByAddr(host.Ip);
    }

    Host Hosts::GetLocalHost()
    {
        wchar_t	wbuf[128] = { 0 };
        unsigned long size = sizeof(wbuf);
        if (!::GetComputerNameW(wbuf, &size))
        {
            //return NULL;
        }
        size = sizeof(wbuf);
        char * host_name = TextEncoder::UnicodeToUtf8(wbuf);
        if (!::GetUserNameW(wbuf, &size))
        {
            //return;
        }
        char * user_name = TextEncoder::UnicodeToUtf8(wbuf);
        Host local;
        local.Name = host_name;
        local.User = user_name;
        local.NickName = "Nick.Matrix";
        delete host_name;
        delete user_name;
        return local;
    }
}
