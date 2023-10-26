#include "chat.h"

//#include <iomanip>
//#include <iostream>

//void Chat::readFromDB() {
//  size_t step = 0;

//  std::vector<QString> query = m_database->GetDataFromDB("SELECT id, sender, receiver, text FROM messages;");
//  if (!query.empty()) {
//      while (step < query.size()) {
//          m_messages.emplace_back(Message(query[step + 1], query[step + 2], query[step + 3]));

//          step += 4;
//        }
//    }
//}

//void Chat::createChat() {
//  std::cout << std::endl;
//  std::cout << "Hello, " << m_user.GetName() << "!" << std::endl;
//  std::cout << "________________________________________" << std::endl;
//  std::cout << std::endl;
//  std::cout << "Type \"@name\" to send private message" << std::endl;
//  std::cout << "Type \"--help\" to show help" << std::endl;
//  std::cout << "Type \"--leave\" to exit from chat room" << std::endl;
//  std::cout << std::endl;

//  const QString from = m_user.GetName();

//  loadHistory(from);

//  bool isLeave = false;
//  while (!isLeave) {
//      std::cout << "[" + from + "]: ";

//      QString to = "all";
//      QString text;

//      getline(std::cin, text);

//      if (text[0] == '-' && text[1] == '-') {
//          isLeave = chatCommand(text);
//          continue;
//        }
//      else if (text[0] == '@') {
//          if (!privateMessage(text, to)) {
//              continue;
//            }
//        }

//      m_database->QueryToDB("INSERT into messages (sender, receiver, text) VALUES ('" + from + "', '" + to + "', '" + text + "');");
//      m_messages.emplace_back(Message(from, to, text));

//      m_log->WriteToLogFile("From " + from + " to " + to + ": " + text);
//    }
//}

//bool Chat::chatCommand(const QString& command) const {
//  if (command == "--help") {
//      std::cout << std::endl;
//      std::cout << "_____________________________________" << std::endl;
//      std::cout << std::endl;
//      std::cout << "--users" << std::setw(18) << "Show all users" << std::endl;
//      std::cout << "--help" << std::setw(14) << "Show help" << std::endl;
//      std::cout << "--leave" << std::setw(23) << "Exit from chat room" << std::endl;
//      std::cout << "--log" << std::setw(33) << "Show last entry in log file" << std::endl;
//      std::cout << std::endl;

//      return false;
//    }

//  if (command == "--leave") {
//      return true;
//    }

//  if (command == "--users") {
//      for (const auto& user : m_users) {
//          std::cout << "User name: " << user.GetName() << std::endl;
//        }

//      return false;
//    }

//  if (command == "--log") {
//      std::cout << "Log: ";
//      m_log->ReadFromLogFile();

//      return false;
//    }

//  std::cout << "Unknown command. Please type \"--help\" for more information"
//            << std::endl;
//  return false;
//}

//bool Chat::privateMessage(QString& text, QString& to) {
//  if (text[1] == ' ') {
//      std::cout << "WARNING: Enter cannot contain space between @ and name"
//                << std::endl;

//      return false;
//    }

//  to.clear();

//  size_t count = 0;

//  for (const auto& ch : text) {
//      if (ch == ' ') {
//          break;
//        }
//      else if (ch == '@') {
//          continue;
//        }
//      else {
//          to += ch;
//          count += 1;
//        }
//    }

//  bool isFind = false;
//  for (const auto& user : m_users) {
//      if (user.GetName() == to) {
//          isFind = true;
//        }
//    }

//  if (!isFind) {
//      std::cout
//          << "WARNING: User with name " << to
//          << " is not in user list. Please type \"--users\" for more information"
//          << std::endl;

//      return false;
//    }

//  if (m_user.GetName() == to) {
//      std::cout << "WARNING: You cannot send message to yourself" << std::endl;

//      return false;
//    }

//  size_t pos = text.find(' ');
//  if (text[pos + 1] == ' ') {
//      std::cout << "WARNING: Enter cannot contain two or more space between name "
//                   "and message"
//                << std::endl;

//      return false;
//    }

//  if (text.size() < count + 2) {
//      std::cout << "WARNING: Message is not typed" << std::endl;

//      return false;
//    }
//  else {
//      text = text.substr(count + 2);
//    }

//  return true;
//}
