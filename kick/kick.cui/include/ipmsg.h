
/*
*
*
*
*	IpMsg Class Header File		In Matrix
*
*	Created by Bonbon	2015.01.18
*
*	Updated by Bonbon	2015.01.20
*
*/

#ifndef _IPMSG_H_
#define _IPMSG_H_


#include <list>
#include "host.h"
#include "environment.h"

#include "msg_mng.h"

namespace Matrix
{
    class IpMsg
    {
    public:
        IpMsg();
        ~IpMsg();

        inline unsigned short Port()
        {
   return m_port;
        }
        inline void Port(unsigned port)
        {
   m_port = port;
        }

        void EntryHost();
        void ExitHost();

        int Run();

    private:

        void MakeBrListEx();
        int BroadcastEntry(unsigned long mode);

    private:
        unsigned short m_port;
        std::list<unsigned long> m_brlist;

        MsgMng m_msg;
    };
}

#endif
