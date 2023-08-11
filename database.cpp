#include "database.h"

#include <iostream>

DataBase::DataBase() : m_connect_status(false)
{
	m_mysql = std::make_shared<MYSQL>();

	mysql_init(m_mysql.get());

	if (m_mysql == NULL) {
		std::cout << "Error: can't create MySQL-descriptor" << std::endl;
	}
}

DataBase::~DataBase()
{
	mysql_close(m_mysql.get());
}

bool DataBase::ConnectToDB() {

	std::cout << "Enter following data to connect to DB:" << std::endl;

	std::string host;
	std::cout << "IP:" << std::endl;
	std::cin >> host;

	unsigned int port = 0;
	std::cout << "Port:" << std::endl;
	std::cin >> port;

	std::string db_name;
	std::cout << "Database name:" << std::endl;
	std::cin >> db_name;

	std::string user;
	std::cout << "User:" << std::endl;
	std::cin >> user;

	std::string password;
	std::cout << "Password:" << std::endl;
	std::cin >> password;

	if (!mysql_real_connect(m_mysql.get(), host.c_str(), user.c_str(), password.c_str(), db_name.c_str(), port, NULL, 0)) {
		std::cout << "Error: can't connect to database " << mysql_error(m_mysql.get()) << std::endl;
	}
	else {
		std::cout << "Connect success!" << std::endl;

		m_connect_status = true;
	}
	return m_connect_status;
}

const std::vector<std::string> DataBase::GetDataFromDB(const std::string& query)
{
	std::vector<std::string> result;

	MYSQL_RES* res;
	MYSQL_ROW row;

	mysql_query(m_mysql.get(), query.c_str());

	if (res = mysql_use_result(m_mysql.get())) {
		while (row = mysql_fetch_row(res)) {
			for (int i = 0; i < mysql_num_fields(res); ++i) {
				result.push_back(row[i]);
			}
		}
	}
	else {
		std::cout << "Error MySql query " << mysql_error(m_mysql.get()) << std::endl;
	}

	mysql_reset_connection(m_mysql.get());

	return result;
}

void DataBase::QueryToDB(const std::string& query) {
	mysql_query(m_mysql.get(), query.c_str());
}