#include "chat.h"

#include <iostream>
#include <string>
#include <memory>

int main() {
  const std::string chat_name = "SF_Chat";
  std::unique_ptr<Chat> chat( new Chat(chat_name));

  chat->Init();

  return 0;
}