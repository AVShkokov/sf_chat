#include "chat.h"

#include <iostream>
#include <string>

int main() {
  const std::string chat_name = "SF_Chat";
  Chat* chat = new Chat(chat_name);
  chat->Init();
  delete chat;

  return 0;
}