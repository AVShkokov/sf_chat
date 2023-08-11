#pragma once

#pragma comment(lib, "libmysql.lib")
#include "mysql.h"

#include <memory>
#include <vector>
#include <string>

class DataBase
{
public:
	DataBase();

	~DataBase();

	bool ConnectToDB();

	const std::vector<std::string> GetDataFromDB(const std::string& query);
	void QueryToDB(const std::string& query);

private:
	std::shared_ptr <MYSQL> m_mysql;
	bool m_connect_status;
};

