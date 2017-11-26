
/*
*
*
*
*	MsgMng Class Header File		In Matrix
*
*	Created by Bonbon	2015.01.19
*
*	Updated by Bonbon	2015.01.20
*
*/


#ifndef _MSG_MNG_H_
#define _MSG_MNG_H_

#include <sstream>
#include "socket.h"
#include "ipmsg_protocol.h"
#include "text_encoder.h"
#include "host.h"

#define MAX_NAMEBUF		80
#define MAX_LISTBUF		(MAX_NAMEBUF * 4)

namespace Matrix
{
    struct RecvBuf {
        struct sockaddr_in	addr;
        int					addrSize;
        int					size;
        char				msgBuf[MAX_UDPBUF];
    };

    struct HostSub {
        char	userName[MAX_NAMEBUF];
        char	hostName[MAX_NAMEBUF];
        ULONG	addr;
        int		portNo;
    };

    struct MsgBuf {
        HostSub	hostSub;
        int		version;
        int		portNo;
        ULONG	packetNo;
        ULONG	command;
        char	msgBuf[MAX_UDPBUF];
        char	exBuf[MAX_UDPBUF];
        char	packetNoStr[256 / 8]; // for IV (256bit)

        MsgBuf() {
   *msgBuf = 0;
   *exBuf = 0;
   *packetNoStr = 0;
        }

        // ¥á¥â¥ê¥³¥Ô©`¹¼s¤Î¤¿¤á¡£
        void	Init(MsgBuf *org) {
   if (org == NULL) {
       memset(this, 0, (char *)&this->msgBuf - (char *)this);
       *msgBuf = 0;
       *exBuf = 0;
       *packetNoStr = 0;
       return;
   }
   memcpy(this, org, (char *)&this->msgBuf - (char *)this);
   strcpy(this->msgBuf, org->msgBuf);
   strcpy(this->exBuf, org->exBuf);
   strcpy(this->packetNoStr, org->packetNoStr);
        }
    };

    class MsgMng
    {
    public:
        MsgMng();
        ~MsgMng();

        unsigned long  MakePacketNo();

        void BroadcastEntrySub(ULONG addr, int port_no, ULONG mode);

        unsigned long MakeMsg(char *buf, int _packetNo, unsigned long command, const char *msg, const char *exmsg, int *packet_len);

        int Send(unsigned long host, int port, unsigned long command, const char *msg, const char *exmsg);

        int UdpSend(unsigned long host_addr, unsigned short port, const char *buf, int len);

        int UdpListen(unsigned short port);

        int ResolveMsg(RecvBuf *buf, MsgBuf *msg);

        int HandleEvent(MsgBuf	msg);

        void MsgBrEntry(MsgBuf *msg);
        void MsgBrExit(MsgBuf *msg);

        unsigned long HostStatus();

    private:
        Socket m_file_listener;
        Socket m_msg_listener;
        Socket m_msg_sender;

        Host m_localhost;
        Hosts m_hosts;

        unsigned long m_packet_no;
    };
}

#endif
