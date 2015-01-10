
/*
*
*
*
*	MySqlHelper Class Header File		In Matrix
*
*	Created by Bonbon	2014.09.27
*
*	Updated by Bonbon	2015.01.10
*
*/

#ifndef _MYSQL_HELPER_H_
#define _MYSQL_HELPER_H_


#include <iostream>
#include <string>

#ifdef WIN32
#include <winsock.h>
#endif

#include <mysql.h>

namespace
{

	class MySqlHelper
	{
	public:

		MySqlHelper();

		MySqlHelper(std::string host, std::string user, std::string pwd, std::string db_name);

		~MySqlHelper();

		void SetDbInfo(std::string host, std::string user, std::string pwd, std::string db_name);
		
		void SetEncode(std::string encode);

		int InitMySQL();

		int ExecQuery(std::string sql);

		int ExecRead(std::string sql);

		std::string ErrorInfo();

	private:

		MYSQL *m_conn;

		std::string m_host;
		std::string m_user;
		std::string m_pwd;
		std::string m_db_name;
		std::string m_encode;
		std::string m_error_info;

	};
}

#endif
