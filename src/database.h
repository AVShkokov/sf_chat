#pragma once

#include <QSqlDatabase>
#include <QSqlQuery>

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
  QSqlDatabase m_db;
  QSqlQuery* m_query;

  bool m_connect_status;
};

