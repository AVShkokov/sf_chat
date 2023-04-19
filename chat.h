#pragma once

#include "message.h"
#include "user.h"

#include <string>
#include <vector>

class Chat {
 public:
  Chat() = default;
  Chat(const std::string& chat_name) : m_chat_name(chat_name) {}

  ~Chat() = default;

  const std::string& GetChatName() const;
  void SetChatName(const std::string& chat_name);

  const void Init();

 private:
  std::string m_chat_name;

  User m_user;
  std::vector<User> m_users;

  std::vector<Message> m_messages;

  const void mainMenu();

  const bool singUp();
  const bool singIn();

  void inputPassword(std::string& password);

  const void loadHistory(const std::string& user_name) const;

  const void createChat();
  const bool privateMessage(std::string& text, std::string& to);

  const bool chatCommand(const std::string& command) const;
};