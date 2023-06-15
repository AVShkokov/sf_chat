#pragma once

#include "message.h"
#include "user.h"

#include <fstream>
#include <string>
#include <vector>

class Chat {
 public:
  Chat() = default;
  Chat(const std::string& chat_name) : m_chat_name(chat_name) {}

  ~Chat() = default;

  const std::string& GetChatName() const;
  void SetChatName(const std::string& chat_name);

  void Init();

 private:
  std::string m_chat_name;

  User m_user;
  std::vector<User> m_users;
  std::string users_file_name = "users";
  std::fstream users_file;

  std::vector<Message> m_messages;
  std::string messages_file_name = "messages";
  std::fstream messages_file;

  void loadUsers();

  void mainMenu();

  const bool singUp();
  const bool singIn();

  void loadHistory(const std::string& user_name);

  void createChat();

  const bool privateMessage(std::string& text, std::string& to);

  const bool chatCommand(const std::string& command) const;
};
