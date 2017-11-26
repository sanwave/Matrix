
/*
*
*
*
*	IpMsg Class Source File		In Matrix
*
*	Created by Bonbon	2015.01.18
*
*	Updated by Bonbon	2015.01.20
*
*/

#include "ipmsg.h"

namespace Matrix
{

    IpMsg::IpMsg()
    {
        m_brlist.clear();
    }
    IpMsg::~IpMsg()
    {

    }

    void IpMsg::EntryHost()
    {
        BroadcastEntry(IPMSG_BR_ENTRY);
    }
    void IpMsg::ExitHost()
    {
        BroadcastEntry(IPMSG_BR_EXIT);
        Sleep(100);
        BroadcastEntry(IPMSG_BR_EXIT);
    }

    int IpMsg::Run()
    {
        m_msg.UdpListen(m_port);
        return 0;
    }

    int IpMsg::BroadcastEntry(unsigned long mode)
    {
        //char cmd[MAX_UDPBUF];
        MakeBrListEx();
        for (unsigned short i = 0; i < m_brlist.size(); ++i)
        {
   m_msg.BroadcastEntrySub(m_brlist.front(), m_port, IPMSG_NOOPERATION | m_msg.HostStatus());
   Sleep(500);
   m_msg.BroadcastEntrySub(m_brlist.front(), m_port, mode | m_msg.HostStatus());
        }
        m_brlist.pop_front();
        return 0;
    }

    void IpMsg::MakeBrListEx()
    {
        int			num = 0, i;// , j;
        AddrInfo	*info = Environment::GetIPAddrs(TRUE, &num);
        if (info && num > 0)
        {
   for (i = num - 1; i >= 0; i--)
   {
       m_brlist.push_back(info[i].br_addr);
   }
        }

        if (!info || num == 0)
        {
   m_brlist.push_back(~0);
        }
    }

}

