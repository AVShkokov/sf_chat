#pragma once

#include "user.h"

#include <string>
#include <vector>

class Chat {
 public:
  Chat() = default;
  Chat(std::string chat_name) : m_chat_name(chat_name) {}

  ~Chat() = default;

  const std::string& GetChatName() const;
  void SetChatName(std::string& chat_name);

  const void Init();

 private:
  std::string m_chat_name;

  std::vector<User> m_users;

  const void mainMenu();
  const void newUserMenu();
};