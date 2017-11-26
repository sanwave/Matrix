
/*
*
*
*
*	Radio Class Source File		In Matrix
*
*	Created by Bonbon	2015.01.18
*
*	Updated by Bonbon	2015.01.18
*
*/

#include "radio.h"

#include <string>
#include <sstream>
#include <thread>

#include "os.h"
#include "convert.h"

#include "http_server.h"
#include "udp_server.h"

namespace Matrix
{
    //int Radio::TcpSend(std::string ip, unsigned short port)
    //{
    //    TcpClient gun;

    //    std::stringstream msg;

    //    for (int i = 0;; ++i)
    //    {
    //        if (i > 99999)
    //        {
    //   i = i % 100000;
    //        }
    //        msg.clear();
    //        msg.str("");
    //        msg << "POST /index.html HTTP/1.0\r\n\r\n"
    //   << Convert::Int2Str(i)
    //   << "Body\r\n";
    //        gun.Send(ip.c_str(), port, msg.str().c_str());
    //        OS::Sleep(2);
    //    }
    //    return 0;
    //}

    //int Radio::UdpSend(std::string ip, unsigned short port)
    //{
    //    return 0;
    //}

    //int Radio::HttpListen(unsigned short port)
    //{
    //    //HttpServer server;
    //    //server.BindAndListen(port);
    //    //server.Run();
    //    return 0;
    //}

    //int Radio::UdpListen(unsigned short port)
    //{
    //    UdpServer server;
    //    server.Listen(port);
    //    server.Run();
    //    return 0;
    //}

    //void Radio::Run()
    //{
    //    std::string ip;
    //    unsigned short port;
    //    unsigned short lis_port;
    //    std::cout << "please input destination ip: ";
    //    std::cin >> ip;
    //    std::cout << "please input destination port: ";
    //    std::cin >> port;
    //    std::cout << "please input listening port: ";
    //    std::cin >> lis_port;

    //    std::thread http_listen(HttpListen, lis_port);
    //    std::thread udp_listen(UdpListen, lis_port);
    //    std::thread tcp_radio(TcpSend, ip, port);
    //    std::thread udp_radio(UdpSend, ip, port);

    //    http_listen.join();
    //    udp_listen.join();
    //    tcp_radio.join();
    //    udp_radio.join();
    //}
}
