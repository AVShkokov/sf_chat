#pragma once

#include <string>

class Chat {
 public:
  Chat() = default;
  Chat(std::string chat_name) : m_chat_name(chat_name) {}

  ~Chat() = default;

  const std::string& GetChatName() const;
  void SetChatName(std::string& chat_name);

  const void Init() const;

 private:
  std::string m_chat_name;

  const void mainMenu() const;
};