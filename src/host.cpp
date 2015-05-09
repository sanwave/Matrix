
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

#include "socket.h"
#include "convert.h"
#include "text_encoder.h"

#ifdef __linux__
// gethostbyname
#include <netdb.h>
#endif

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

    void Host::SetAddr(const char * addr)
    {
        const char * port_ptr = strchr(addr, ':');
        std::string str;
        if (NULL == port_ptr)
        {
            str = addr;
            Port = 80;
        }
        else
        {
            str = std::string(addr, port_ptr - addr);
            Port = Convert::Str2Int(std::string(port_ptr + 1));
        }
        if (IsDomain(str.c_str()))
        {
            Domain = str;
            SetIp(Resolve(Domain.c_str()));
        }
        else
        {
            Ip = str;
        }
    }

    int Host::IsDomain(const char* value)
    {
        int bRet = 0;
        if (NULL == value)
        {
            return -1;
        }
        const char* p = value;
        for (; *p != '\0'; p++)
        {
            if ((isalpha(*p)) && (*p != '.'))
            {
                bRet = 1;
                break;
            }
        }
        return bRet;
    }

    unsigned long Host::Resolve(const char * domain)
    {
        Socket::Init();
        struct hostent *hptr = NULL;
        struct sockaddr_in addr;
        hptr = gethostbyname(domain);
        Socket::Uninit();

        if (NULL == hptr)
        {
            return 0;
        }
        switch (hptr->h_addrtype)
        {
        case AF_INET:
        case AF_INET6:
            memcpy(&addr.sin_addr.s_addr, hptr->h_addr_list[0], hptr->h_length);
            //inet_ntop(hptr->h_addrtype, *pptr, str, sizeof(str));
            return addr.sin_addr.s_addr;

        default:
            return 0;
        }
    }

    std::string Host::Addr() const
    {
        return Ip + ":" + Convert::Int2Str(Port);
    }

    std::string Host::DomainAddr() const
    {
        if (Domain.empty())
            return Addr();
        else if (DEFAULT_HTTP_PORT != Port)
            return Domain + ":" + Convert::Int2Str(Port);
        else
            return Domain;
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
        for (iter = m_hosts.begin(); iter != m_hosts.end(); ++iter)
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
#ifdef WIN32
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
#else
        Host local;
        return local;
#endif
    }
}
