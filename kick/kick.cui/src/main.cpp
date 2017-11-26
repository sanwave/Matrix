
/*
*
*
*
*
*	Program Entry
*
*	Main Function File		In Matrix
*
*	Created by Bonbon	2015.01.08
*
*	Updated by Bonbon	2015.02.02
*
*/

//system()
#include <cstdlib>
#include <cstdio>
#include <string>
#include <cstring>
#include <thread>
#include <sstream>

#ifdef WIN32
#include "ipmsg.h"
#else
#include <termios.h>
#endif

#include "os.h"
#include "file.h"
#include "radio.h"
#include "convert.h"
#include "environment.h"
#include "datetime.h"
#include "string_handler.h"
#include "udp_server.h"
#include "http_client.h"
#include "http_server.h"
#include "http_request.h"
#include "hls_client.h"

using namespace Matrix;

void test_http_client()
{
    std::cout << "========================     Http Simulate Client     ========================\r\n\r\n";
    std::cout << "Please input request url:" << std::endl;
    std::string url = "http://172.30.14.82/Message.aspx";
    url = "http://172.30.14.82/Message.aspx";
    url = "http://www.baidu.com";
    url = "http://c4.staticflickr.com/4/3637/13085053613_5a2afba249_n.jpg";
    //url = "http://p10.tuku.cc:8899/300/%E9%BE%99%E7%A5%9E/%E5%8D%B71.zip";
    //url = "http://www.wired.com/wp-content/uploads/2014/09/Interstellar_ALT_Artowrk.jpeg";
    //url = "http://img2.wikia.nocookie.net/__cb20141003183252/interstellarfilm/images/b/bd/Interstellar-2014-Movie-Poster.jpg";
    std::cout << "e.g.1: " << url << std::endl;
    HttpClient client;
    //std::cin >> url;
    while (1)
    {
        client.Get(url.c_str(), true);        
        OS::Pause();
    }
}

void test_player_client()
{
    HlsClient client;
    std::string url = "http://172.21.10.36:9199/live/cctv1.m3u8?shifttime=1423019500&shiftend=1423020000";
    std::cout << std::endl;
    std::cout << "========================     GeHua Simulate Client     ========================\r\n\r\n";
    std::cout << "Please input request url:" << std::endl;
    std::cout << "e.g.1: " << "http://172.21.10.36:9199/live/cctv1.m3u8" << std::endl;
    std::cout << "e.g.2: " << "http://172.21.10.36:9390/GTIT0120120524000121.m3u8" << std::endl;
    //std::cin >> url;
    url = "http://172.21.10.36:8388/live/cctv1_800.m3u8";
    url = "http://hls.yun.gehua.net.cn:8088//vod/trans/20141216/GMOV0120141216200300/GTIT0120141216200300_800.m3u8";
    while (1)
    {
        std::cout << "\r\n=============================================================================" << std::endl;
        client.ReqContent(url.c_str());
        std::cout << std::endl;
        OS::Pause();
    }
}

void test_http_server()
{
    HttpServer server;
    server.Init(9200);
    server.Run();
}

void test_udp_server()
{
    UdpServer server;
    server.Listen(9200);
    server.Run();
}

void test_udp_client()
{
    UdpServer client;
    struct cost
    {
        int food;
        int electronics;
    }me;
    me.food = 2000;
    me.electronics = 5000;
    while (1)
    {
        ++me.food;
        ++me.electronics;
        client.Send("10.10.64.26", 9200, (char *)&me, sizeof(cost));
        OS::Sleep(100);
    }
}

void cui_hanlder()
{
    std::cout << CRLF << CRLF;
    std::cout << "=========     CDN Simulate Client     =========" << std::endl << std::endl;
    std::cout << "Please choose item to test:" << std::endl;
    std::cout << "v. Simulate Player Client" << std::endl;
    std::cout << "s. Http Server Test" << std::endl;
    std::cout << "c. Http Client Test" << std::endl;
    std::cout << "u. Udp Server Test" << std::endl;
    std::cout << "r. Udp Client Test" << std::endl;

    char choose = 0;
    std::cin >> choose;

    switch (choose)
    {
    case 'v':
        test_player_client();
        break;

    case 's':
        test_http_server();
        break;

    case 'c':
        test_http_client();
        break;

    case 'u':
        test_udp_server();
        break;

    case 'r':
        test_udp_client();
        break;

    default:
        std::cout << "the program can't recognize your input." << std::endl;
        std::cout << "the program will exit." << std::endl;
        OS::Sleep(3000);
        break;
    }
}

void print_program_info()
{
    std::cout << std::endl;
    std::cout << " Kick" << std::endl;
    std::cout << "-c, --cui                             command ui." << std::endl;
    std::cout << "-g, --get-request                     send get http msg." << std::endl;
    std::cout << "-d, --download                        send get http msg and save as file." << std::endl;
    std::cout << "-p, --post-request                    send post http msg." << std::endl;
    std::cout << "-r, --request                         send get/post http msg." << std::endl;
    std::cout << "-h, --hls-request                     send request to hls server." << std::endl;
}

int main(int argc, char **argv)
{
    if (1 == argc)
    {
        print_program_info();
        cui_hanlder();          // temporarily
    }
    else if (2 == argc)
    {
        std::string cmd = *(argv + 1);
        if ("-c" == cmd || "--cui" == cmd)
        {
            cui_hanlder();
        }
        else
        {
            print_program_info();
        }
    }
    else if (3 == argc)
    {
        std::string cmd = *(argv + 1);
        std::string para1 = *(argv + 2);
        if ("-g" == cmd || "--get-request" == cmd)
        {
            HttpClient client;
            client.Get(para1.c_str());
        }
        else if ("-d" == cmd || "--download" == cmd)
        {
            HttpClient client;
            client.Get(para1.c_str(), true);
        }
        else if ("-h" == cmd || "--hls-request" == cmd)
        {
            HlsClient client;
            client.ReqContent(para1.c_str());
        }
        else
        {
            print_program_info();
        }
    }
    else if (4 == argc)
    {
        std::string cmd = *(argv + 1);
        std::string para1 = *(argv + 2);
        std::string para2 = *(argv + 3);
        if ("-p" == cmd || "--post-request" == cmd)
        {
            HttpClient client;
            client.Post(para1.c_str(), para2.c_str());
        }
        else if ("-h" == cmd || "--hls-request" == cmd)
        {
            HlsClient client;
            client.ReqContent(para1.c_str());
        }
        else if ("-r" == cmd || "--request" == cmd)
        {
            HttpClient client;
            std::string resp_msg;
            client.Request(para1, para2, resp_msg);
            std::cout << resp_msg;
        }
        else
        {
            print_program_info();
        }
    }
    else
    {
        print_program_info();
    }
    return 0;
}
