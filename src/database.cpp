#include "database.h"

#include <QSqlError>
#include <QSqlRecord>
#include <QVariant>

#include <iostream>

DataBase::DataBase() : m_connect_status(false)
{
}

DataBase::~DataBase()
{
  m_db.close();
}

bool DataBase::ConnectToDB(QString& message) {
  m_db = QSqlDatabase::addDatabase("QSQLITE");

  m_db.setDatabaseName("./chatDB.db");

  if(!m_db.open()) {
      message = QString("Error: can't connect to database %1").arg(m_db.lastError().text());
    }
  else {
      m_query = new QSqlQuery(m_db);
      m_query->exec("CREATE TABLE if not exists users ( "
                    "id         SERIAL PRIMARY KEY, "
                    "name       VARCHAR(20) not null, "
                    "login      VARCHAR(20) not null, "
                    "password   VARCHAR(10) not null "
                    ");");

      m_query->exec("CREATE TABLE if not exists messages( "
                    "id         SERIAL PRIMARY KEY, "
                    "sender     VARCHAR(10) not null, "
                    "receiver	 VARCHAR(10) not null, "
                    "text	     text "
                    ");");

      m_connect_status = true;
    }

  return m_connect_status;
}

const QVector<QString> DataBase::GetDataFromDB(const QString& query)
{
  QVector<QString> result;

  if(m_query->exec(query)) {
      QSqlRecord record = m_query->record();

      while(m_query->next()) {
          for (int i = 0; i < record.count(); ++i) {
              result.push_back(m_query->value(i).toString());
            }
        }
    }
  else {
      std::cout << "Error sql query " << m_db.lastError().text().toStdString() << std::endl;
    }

  return result;
}

void DataBase::QueryToDB(const QString& query) {
  m_query->exec(query);
}
