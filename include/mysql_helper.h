
/*
*
*
*
*	MySqlHelper Class		In Matrix
*
*	Created by Bonbon	2014.09.27
*
*/

#ifndef _MYSQL_HELPER_H_
#define _MYSQL_HELPER_H_



#ifndef MATRIX
#include <iostream>
#include <string>
#else
#include "common.h"
#endif

#ifdef WIN32
#include <winsock.h>
#endif

#include <mysql.h>

#pragma comment(lib,"libmysql.lib") 

namespace
{

	class MySqlHelper
	{
	public:

		MySqlHelper() : m_conn(NULL), m_encode("gbk")
		{
			MySqlHelper("", "", "", "");
		}

		MySqlHelper(std::string host, std::string user, std::string pwd, std::string db_name)
			:m_conn(NULL), m_host(host), m_user(user), m_pwd(pwd),
			m_db_name(db_name), m_encode("gbk")
		{
			//初始化数据库
			if (0 != mysql_library_init(0, NULL, NULL))
			{
				m_error_info = "mysql_library_init() failed";
			}
		}

		~MySqlHelper()
		{
			//mysql_close(&m_conn);
			mysql_server_end();
			std::cout << "~MySqlHelper" << std::endl;
		}

		void SetDbInfo(std::string host, std::string user, std::string pwd, std::string db_name)
		{
			m_host = host;
			m_user = user;
			m_pwd = pwd;
			m_db_name = db_name;
		}
		
		void SetEncode(std::string encode)
		{
			m_encode = encode;
		}

		int InitMySQL()
		{
			//初始化数据结构
			if (NULL == (m_conn = mysql_init(m_conn)))
			{
				m_error_info = "mysql_init() failed";
				return -1;
			}

			//在连接数据库之前，设置编码
			if (0 != mysql_options(m_conn, MYSQL_SET_CHARSET_NAME, m_encode.c_str()))
			{
				m_error_info = "mysql_options() failed";
				return -1;
			}

			//连接数据库
			if (NULL == mysql_real_connect(m_conn, m_host.c_str(), m_user.c_str(), m_pwd.c_str(),
				m_db_name.c_str(), 3306, NULL, 0))
			{
				m_error_info = "mysql_real_connect() failed";
				return -1;
			}

			return 0;
		}

		int ExecQuery(std::string sql)
		{
			if (0 != mysql_query(m_conn, sql.c_str()))
			{
				m_error_info = "mysql_query() execute sql command failed\n";
				m_error_info += "Error Info:" + std::string(mysql_error(m_conn));
				mysql_close(m_conn);
				return -1;
			}
			return 0;
		}

		int ExecRead(std::string sql)
		{
			MYSQL_RES *result = NULL;
			if (0 == mysql_query(m_conn, sql.c_str()))
			{
				//一次性取得数据集
				result = mysql_store_result(m_conn);
				//取得并打印行数
				my_ulonglong rowcount = mysql_num_rows(result);
				std::cout << "row count: " << rowcount << std::endl;

				//取得并打印各字段的名称
				unsigned int fieldcount = mysql_num_fields(result);
				MYSQL_FIELD *field = NULL;
				for (unsigned int i = 0; i < fieldcount; i++)
				{
					field = mysql_fetch_field_direct(result, i);
					std::cout << field->name << "\t";
				}
				std::cout << std::endl;

				//打印各行
				MYSQL_ROW row = NULL;
				row = mysql_fetch_row(result);
				while (NULL != row)
				{
					for (unsigned int i = 0; i < fieldcount; i++)
					{
						std::cout << ((row[i] == NULL) ? "" : row[i]) << "\t";
					}
					std::cout << std::endl;
					row = mysql_fetch_row(result);
				}
			}
			else
			{
				m_error_info = "mysql_query() select data failed\n";
				m_error_info += "Error Info:" + std::string(mysql_error(m_conn));
				mysql_close(m_conn);
				return -1;
			}
			mysql_free_result(result);
			return 0;
		}

		std::string ErrorInfo()
		{
			return m_error_info;
		}

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
