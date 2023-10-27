#pragma once

#include <QSqlDatabase>
#include <QSqlQuery>

#include <QString>
#include <QVector>

class DataBase
{
public:
  DataBase();

  ~DataBase();

  bool ConnectToDB(QString& message);

  const QVector<QString> GetDataFromDB(const QString& query);
  void QueryToDB(const QString& query);

private:
  QSqlDatabase m_db;
  QSqlQuery* m_query;

  bool m_connect_status;
};

