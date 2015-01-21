
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

namespace Matrix
{
	class Host
	{
	public:
		std::string Name;
		std::string User;
		std::string Ip;
		unsigned short Port;
	};

}

#endif
