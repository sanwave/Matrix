
/*
*
*
*
*	MySqlHelper Class Source File		In Matrix
*
*	Created by Bonbon	2014.09.27
*
*	Updated by Bonbon	2015.01.10
*
*/

#include "mysql_helper.h"

namespace Matrix
{
    MySqlHelper::MySqlHelper() : m_conn(NULL), m_encode("utf8")
    {}

    MySqlHelper::MySqlHelper(std::string host, std::string user, std::string pwd, std::string db_name)
        : m_conn(NULL), m_host(host), m_user(user), m_pwd(pwd),
        m_db_name(db_name), m_encode("utf8")
    {}

    MySqlHelper::MySqlHelper(const MySqlHelper & src)
        :m_conn(NULL)
    {
        m_host = src.m_host;
        m_user = src.m_user;
        m_pwd = src.m_pwd;
        m_db_name = src.m_db_name;
        m_encode = src.m_encode;
        m_error_info = src.m_error_info;

        if (NULL != src.m_conn)
        {
            InitMySQL();
        }
    }

    MySqlHelper::~MySqlHelper()
    {
        mysql_close(m_conn);
        mysql_server_end();
        std::cout << "~MySqlHelper" << std::endl;
    }

    void MySqlHelper::SetDbInfo(std::string host, std::string user, std::string pwd, std::string db_name)
    {
        m_host = host;
        m_user = user;
        m_pwd = pwd;
        m_db_name = db_name;
    }

    void MySqlHelper::SetEncode(std::string encode)
    {
        m_encode = encode;
    }

    int MySqlHelper::InitMySQL()
    {
        //initialize the mysql connection library
        if (0 != mysql_library_init(0, NULL, NULL))
        {
            m_error_info = "mysql_library_init() failed";
        }

        //initialize the mysql data types
        if (NULL == (m_conn = mysql_init(m_conn)))
        {
            m_error_info = "mysql_init() failed";
            return -1;
        }

        //set text encode before connect to mysql server
        if (0 != mysql_options(m_conn, MYSQL_SET_CHARSET_NAME, m_encode.c_str()))
        {
            m_error_info = "mysql_options() failed";
            return -1;
        }

        //connect to mysql server
        if (NULL == mysql_real_connect(m_conn, m_host.c_str(), m_user.c_str(), m_pwd.c_str(),
            m_db_name.c_str(), 3306, NULL, 0))
        {
            m_error_info = "mysql_real_connect() failed";
            return -1;
        }

        return 0;
    }

    int MySqlHelper::ExecQuery(std::string sql)
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

    int MySqlHelper::ExecRead(std::string sql, void(*handler)(MYSQL_RES *))
    {
        MYSQL_RES *result = NULL;
        if (0 == mysql_real_query(m_conn, sql.c_str(), sql.length()))
        {
            //get all the data queried
            result = mysql_store_result(m_conn);
            ////print line number
            //my_ulonglong rowcount = mysql_num_rows(result);
            //std::cout << "row count: " << rowcount << std::endl;

            //print table header name
            //unsigned int fieldcount = mysql_num_fields(result);
            //MYSQL_FIELD *field = NULL;
            //for (unsigned int i = 0; i < fieldcount; i++)
            //{
            //    field = mysql_fetch_field_direct(result, i);
            //    std::cout << field->name << "\t";
            //}
            //std::cout << std::endl;

            ////print all lines data
            //MYSQL_ROW row = NULL;
            //row = mysql_fetch_row(result);
            //while (NULL != row)
            //{
            //    for (unsigned int i = 0; i < fieldcount; i++)
            //    {
            //        std::cout << ((row[i] == NULL) ? "" : row[i]) << "\t";
            //    }
            //    std::cout << std::endl;
            //    row = mysql_fetch_row(result);
            //}
        }
        else
        {
            m_error_info = "mysql_query() select data failed\n";
            m_error_info += "Error Info:" + std::string(mysql_error(m_conn));
            mysql_close(m_conn);
            return -1;
        }
        if (NULL != result && NULL != handler)
        {
            handler(result);
        }
        mysql_free_result(result);
        return 0;
    }

    std::string MySqlHelper::ErrorInfo()
    {
        return m_error_info;
    }
}
