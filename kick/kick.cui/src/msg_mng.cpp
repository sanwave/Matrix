
/*
*
*
*
*	MsgMng Class Source File		In Matrix
*
*	Created by Bonbon	2015.01.19
*
*	Updated by Bonbon	2015.01.20
*
*/

#include "msg_mng.h"

#include "log.h"
#include "datetime.h"

namespace Matrix
{
    int LocalNewLineToUnix(const char *src, char *dest, int maxlen)
    {
        char	*sv_dest = dest;
        char	*max_dest = dest + maxlen - 1;
        int		len = 0;

        while (*src && dest < max_dest) {
   if ((*dest = *src++) != '\r') dest++;
        }
        *dest = 0;

        return	int(dest - sv_dest);
    }

    int UnixNewLineToLocal(const char *src, char *dest, int maxlen)
    {
        char	*sv_dest = dest;
        char	*max_dest = dest + maxlen - 1;

        while (*src && dest < max_dest) {
   if ((*dest = *src++) == '\n' && dest + 1 < max_dest) {
       *dest++ = '\r';
       *dest++ = '\n';
   }
   else dest++;
        }
        *dest = 0;

        return	int(dest - sv_dest);
    }

    char *strncpyz(char *dest, const char *src, size_t num)
    {
        char	*sv = dest;

        while (num-- > 0)
        if ((*dest++ = *src++) == '\0')
   return	sv;

        if (sv != dest)		// num > 0
   *(dest - 1) = 0;
        return	sv;
    }

    char *separate_token(char *buf, char separetor, char **handle)
    {
        char	*_handle;

        if (handle == NULL)
   handle = &_handle;

        if (buf)
   *handle = buf;

        if (*handle == NULL || **handle == 0)
   return	NULL;

        while (**handle == separetor)
   (*handle)++;
        buf = *handle;

        if (**handle == 0)
   return	NULL;

        while (**handle && **handle != separetor)
   (*handle)++;

        if (**handle == separetor)
   *(*handle)++ = 0;

        return	buf;
    }

    MsgMng::MsgMng() :m_packet_no(0)
    {
        m_localhost = Hosts::GetLocalHost();
    }
    MsgMng::~MsgMng()
    {

    }

    unsigned long MsgMng::MakePacketNo()
    {
        ULONG now = DateTime::UnixTime();

        if (now > m_packet_no) {
   m_packet_no = now;
        }

        return m_packet_no++;
    }

    void MsgMng::BroadcastEntrySub(ULONG addr, int port_no, ULONG mode)
    {
        if (addr != 0)
        {
   Send(addr, port_no, mode | HostStatus(), m_localhost.NickName.c_str(), "Group");
        }
    }

    unsigned long MsgMng::MakeMsg(char *buf, int _packetNo, unsigned long command, const char *msg, const char *exmsg, int *packet_len)
    {
        int			cmd = GET_MODE(command);
        BOOL		is_br_cmd = cmd == IPMSG_BR_ENTRY ||
   cmd == IPMSG_BR_EXIT ||
   cmd == IPMSG_BR_ABSENCE ||
   cmd == IPMSG_NOOPERATION ? TRUE : FALSE;
        BOOL		is_utf8 = (command & IPMSG_UTF8OPT);
        //HostSub		*host = is_utf8 ? &local : &localA;
        char		*out_buf = NULL;
        char		*out_exbuf = NULL;
        const char	*msg_org = msg;
        const char	*exMsg_org = exmsg;
        int			len = 0;
        size_t			ex_len = 0;
        int			&pkt_len = packet_len ? *packet_len : len;
        int			max_len = MAX_UDPBUF;
        //BOOL		is_ascii;

        if (is_utf8)
        {
   pkt_len = sprintf(buf, "%d:%u:%s:%s:%u:", IPMSG_VERSION, _packetNo,
       m_localhost.User.c_str(), m_localhost.Name.c_str(), command);
        }
        else
        {
   pkt_len = sprintf(buf, "%d:%u:%s:%s:%u:", IPMSG_VERSION, _packetNo,
       TextEncoder(m_localhost.User).Ansi(), TextEncoder(m_localhost.Name).Ansi(), command);
        }


        max_len -= ex_len;

        if (msg) {
   pkt_len += LocalNewLineToUnix(msg, buf + pkt_len, max_len - pkt_len);
        }

        pkt_len++;

        if (is_br_cmd) {
   buf[pkt_len++] = 0;
   pkt_len += sprintf(buf + pkt_len, "\nUN:%s\nHN:%s\nNN:%s\nGN:%s",
       m_localhost.User.c_str(), m_localhost.Name.c_str(), msg_org, exMsg_org);
        }

        delete[] out_exbuf;
        delete[] out_buf;

        return	_packetNo;
    }

    int MsgMng::Send(unsigned long host, int port, unsigned long command, const char *msg, const char *exmsg)
    {
        char	buf[MAX_UDPBUF];
        int		trans_len;

        MakeMsg(buf, MakePacketNo(), command, msg, exmsg, &trans_len);
        return	UdpSend(host, port, buf, trans_len);
    }

    int MsgMng::UdpSend(unsigned long addr, unsigned short port, const char *buf, int len)
    {
        sockaddr_in target;
        target.sin_family = AF_INET;
        target.sin_addr.s_addr = addr;
        target.sin_port = htons(port);

        Host host;
        host.SetIp(addr);
        std::cout << DateTime::Now() << "    DEBUG    send msg: " << buf << " to addr: " << host.Ip << std::endl;

        m_msg_sender.SendTo(buf, len, 0, (sockaddr *)&target, sizeof(target));

        return 0;
    }

    int MsgMng::UdpListen(unsigned short port)
    {
        m_msg_listener.Bind(INADDR_ANY, port);

        char rx_buf[REQ_BUF_SIZE] = { 0 };
        while (1)
        {
   struct sockaddr_in host_addr;
   memset(&host_addr, 0, sizeof(sockaddr_in));
   int sin_size = sizeof(sockaddr_in);
   memset(rx_buf, 0, sizeof(rx_buf));
   int ret = m_msg_listener.RecvFrom(rx_buf, sizeof(rx_buf), 0, (sockaddr *)&host_addr, &sin_size);
   if (ret == -1)
   {
       Log::Write(LOG_ERROR, "recvfrom error.");
       continue;
   }

   char ip[22] = { 0 };
   inet_ntop(AF_INET, &host_addr.sin_addr, ip, 22);
   unsigned short port = ntohs(host_addr.sin_port);

   std::stringstream log_info;
   log_info << "Recved message: " << rx_buf << " from " << ip << ":" << port << "";

   Log::Write(LOG_INFO, log_info.str().c_str());
   std::cout << DateTime::Now().c_str() << "    "
       << "INFO" << "    "
       << log_info.str() << std::endl;

   RecvBuf req;
   MsgBuf msg;
   strncpy(req.msgBuf, rx_buf, strlen(rx_buf));
   req.addr = host_addr;
   ResolveMsg(&req, &msg);
   HandleEvent(msg);

   log_info.str("");
   log_info << "more info ..." << std::endl;
   log_info << "Host name: " << msg.hostSub.hostName << "; user: " << msg.hostSub.userName << std::endl;
   log_info << "Msg command: " << msg.command << std::endl;
   log_info << "Msg content: " << msg.msgBuf << std::endl;

   Log::Write(LOG_INFO, log_info.str().c_str());
   std::cout << DateTime::Now().c_str() << "    "
       << "INFO" << "    "
       << log_info.str() << std::endl;

   Sleep(200);
        }

    }

    int MsgMng::HandleEvent(MsgBuf	msg)
    {
        switch (GET_MODE(msg.command)) {
        case IPMSG_BR_ENTRY:
   MsgBrEntry(&msg);
   return	TRUE;

        case IPMSG_BR_EXIT:
   MsgBrExit(&msg);
   return	TRUE;

        case IPMSG_ANSENTRY:
   //MsgAnsEntry(&msg);
   return	TRUE;

        case IPMSG_BR_ABSENCE:
   //MsgBrAbsence(&msg);
   return	TRUE;

        case IPMSG_SENDMSG:
   //MsgSendMsg(&msg);
   break;

        case IPMSG_RECVMSG:
   //MsgRecvMsg(&msg);
   break;

        case IPMSG_READMSG:
        case IPMSG_ANSREADMSG:
   //MsgReadMsg(&msg);
   break;

        case IPMSG_BR_ISGETLIST2:
   //MsgBrIsGetList(&msg);
   return	TRUE;

        case IPMSG_OKGETLIST:
   //MsgOkGetList(&msg);
   return	TRUE;

        case IPMSG_GETLIST:
   //MsgGetList(&msg);
   return	TRUE;

        case IPMSG_ANSLIST:
   //MsgAnsList(&msg);
   return	TRUE;

        case IPMSG_GETINFO:
   //MsgGetInfo(&msg);
   break;

        case IPMSG_SENDINFO:
   //MsgSendInfo(&msg);
   break;

        case IPMSG_GETPUBKEY:
   //MsgGetPubKey(&msg);
   break;

        case IPMSG_ANSPUBKEY:
   //MsgAnsPubKey(&msg);
   break;

        case IPMSG_GETABSENCEINFO:
   //MsgGetAbsenceInfo(&msg);
   break;

        case IPMSG_SENDABSENCEINFO:
   //MsgSendAbsenceInfo(&msg);
   break;

        case IPMSG_RELEASEFILES:
   //MsgReleaseFiles(&msg);
   break;
        }

        return	TRUE;
    }

    int MsgMng::ResolveMsg(RecvBuf *buf, MsgBuf *msg)
    {
        char	*exStr = NULL, *tok, *p;
        char	*exStr2 = NULL;
        char	*userName, *hostName;
        int		len, exLen = 0;

        len = (int)strlen(buf->msgBuf); // main message

        if (buf->size > len + 1) { // ex message (group name or attached file)
   exStr = buf->msgBuf + len + 1;
   exLen = (int)strlen(exStr);
   if (buf->size > len + 1 + exLen + 1) { // ex2 message (utf8 entry)
       exStr2 = exStr + exLen + 1;
   }
        }

        msg->hostSub.addr = buf->addr.sin_addr.s_addr;
        msg->hostSub.portNo = buf->addr.sin_port;

        if ((tok = separate_token(buf->msgBuf, ':', &p)) == NULL)
   return	FALSE;
        if ((msg->version = atoi(tok)) != IPMSG_VERSION)
   return	FALSE;

        if ((tok = separate_token(NULL, ':', &p)) == NULL)
   return	FALSE;
        msg->packetNo = strtoul(tok, 0, 10);
        strncpyz(msg->packetNoStr, tok, sizeof(msg->packetNoStr)); // for IV

        if ((userName = separate_token(NULL, ':', &p)) == NULL)
   return	FALSE;

        if ((hostName = separate_token(NULL, ':', &p)) == NULL)
   return	FALSE;

        if ((tok = separate_token(NULL, ':', &p)) == NULL)
   return	FALSE;
        msg->command = atol(tok);
        BOOL	is_utf8 = (msg->command & IPMSG_UTF8OPT);

        is_utf8 = !is_utf8;

        strncpyz(msg->hostSub.userName, is_utf8 ? userName : TextEncoder(userName).Utf8(), sizeof(msg->hostSub.userName));
        strncpyz(msg->hostSub.hostName, is_utf8 ? hostName : TextEncoder(hostName).Utf8(), sizeof(msg->hostSub.hostName));

        int		cnt = 0;
        *msg->msgBuf = 0;
        if ((tok = separate_token(NULL, 0, &p))) // 改行をUNIX形式からDOS形式に変換
        {
   if (!is_utf8) {
       tok = TextEncoder(tok).Utf8();
   }
   UnixNewLineToLocal(tok, msg->msgBuf, MAX_UDPBUF);
        }

        if (exStr) {
   if (exStr[0] != '\n') {
       if ((msg->command & IPMSG_UTF8OPT) == 0) {
  exStr = TextEncoder(exStr).Utf8();
       }
       strncpyz(msg->exBuf, exStr, sizeof(msg->exBuf));
   }
   else if (exStr2 == NULL) {
       exStr2 = exStr;
   }

   if (exStr2 && exStr2[0] == '\n' && (msg->command & IPMSG_CAPUTF8OPT)) {
       for (tok = separate_token(exStr2, '\n', &p); tok; tok = separate_token(NULL, '\n', &p)) {
  if (strncmp(tok, "UN:", 3) == 0) {
      strncpyz(msg->hostSub.userName, tok + 3, sizeof(msg->hostSub.userName));
  }
  else if (strncmp(tok, "HN:", 3) == 0) {
      strncpyz(msg->hostSub.hostName, tok + 3, sizeof(msg->hostSub.hostName));
  }
  else if (strncmp(tok, "NN:", 3) == 0) {
      switch (GET_MODE(msg->command)) {
      case IPMSG_BR_ENTRY: case IPMSG_BR_ABSENCE:
 strncpyz(msg->msgBuf, tok + 3, sizeof(msg->msgBuf));
 break;
      }
  }
  else if (strncmp(tok, "GN:", 3) == 0) {
      switch (GET_MODE(msg->command)) {
      case IPMSG_BR_ENTRY: case IPMSG_BR_ABSENCE:
 strncpyz(msg->exBuf, tok + 3, sizeof(msg->exBuf));
 break;
      }
  }
       }
   }
        }

        return	TRUE;
    }

    unsigned long MsgMng::HostStatus()
    {
        return	(/*cfg->DialUpCheck*/false ? IPMSG_DIALUPOPT : 0)
   | (/*cfg->AbsenceCheck*/false ? IPMSG_ABSENCEOPT : 0)
   | (/*msgMng->IsAvailableTCP()*/true ?
   (IPMSG_FILEATTACHOPT | (/*(cfg->ClipMode & CLIP_ENABLE)*/true ? IPMSG_CLIPBOARDOPT : 0)) : 0)
   | (/*GetLocalCapa(cfg)*/true ? IPMSG_ENCRYPTOPT : 0)
   | IPMSG_CAPUTF8OPT
   | IPMSG_ENCEXTMSGOPT;
    }

    void MsgMng::MsgBrEntry(MsgBuf *msg)
    {
        int			command = IPMSG_ANSENTRY | HostStatus();
        if (msg->command & IPMSG_CAPUTF8OPT) command |= IPMSG_UTF8OPT;

        Host * host = new Host();
        host->Name = msg->hostSub.hostName;
        host->User = msg->hostSub.userName;
        host->SetIp(msg->hostSub.addr);
        host->Port = msg->hostSub.portNo;
        //host->NickName=msg->

        Send(msg->hostSub.addr, host->Port, command, m_localhost.NickName.c_str(), "WorkGroup");
        Log::Write(LOG_INFO, "Add a host" + host->Ip);
        m_hosts.AddHost(host);
    }

    void MsgMng::MsgBrExit(MsgBuf *msg)
    {
        Host * host = m_hosts.GetHostByAddr(msg->hostSub.addr);
        m_hosts.RemoveHost(host);
    }

}
