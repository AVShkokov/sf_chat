#include "chat.h"

#include <iostream>
#include <memory>
#include <string>

int main() {
  const std::string chat_name = "SF_Chat";
  std::unique_ptr<Chat> chat = std::make_unique<Chat>(chat_name);

  chat->Init();

  return 0;
}