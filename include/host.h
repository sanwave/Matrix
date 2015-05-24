
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

#define MAX_DOMAIN_NUM 1024
#define DEFAULT_HTTP_PORT 80

namespace Matrix
{
    class Host
    {
    public:
        std::string Name;
        std::string User;
        std::string Ip;
        unsigned short Port;
        std::string Domain;
        std::string NickName;

        // get addr(ip:port) string, e.g. 172.21.11.169:8086
        std::string Addr() const;
        // get addr with domain(domain, domain:port or ip:port) string, e.g. www.google.com
        std::string DomainAddr() const;
        // set ip value
        void SetIp(unsigned long ip);
        // set addr value like "domain", "domain:port", "ip:port"
        void SetAddr(const char *);
        // if the string value is domain name, return true; otherwise, return false
        int IsDomain(const char* value);
        // resolve the domain name to ip addr
        unsigned long Host::Resolve(const char * domain);
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
