#pragma once

//#include "message.h"
//#include "user.h"
//#include "database.h"
//#include "logger.h"

//#include <string>
//#include <vector>
//#include <memory>

//class Chat {
//public:
//  Chat() = default;
//  ~Chat() = default;

//private:
//  User m_user;
//  std::vector<User> m_users;
//  std::vector<Message> m_messages;

//  std::shared_ptr<DataBase> m_database = std::make_shared<DataBase>();

//  const QString m_log_file_name = "log.txt";
//  Logger* m_log = new Logger(m_log_file_name);

//  void readFromDB();

//  void loadHistory(const QString& user_name);

//  void createChat();

//  bool privateMessage(QString& text, QString& to);

//  bool chatCommand(const QString& command) const;
//};
