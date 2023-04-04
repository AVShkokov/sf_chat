#pragma once

#include "user.h"
#include "message.h"

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
  
  const void singUp();
  const bool singIn(User& user);
  
  const void loadHistory(const std::vector<std::string>& messages) const;

  const void createChat(const User& user, Message* messages);
};