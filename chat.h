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

  std::vector<User> m_users;

  const void mainMenu();

  const void singUp();
  const bool singIn(User& user);

  const void loadHistory(const Message* messages,
                         const std::string& from) const;

  const void createChat(const User& user, Message* messages);

  const bool chatCommand(const std::string& message) const;
};