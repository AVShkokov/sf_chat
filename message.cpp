#include "message.h"

#include <iostream>

void Message::SetFrom(const std::string& from) {
  m_message[0] = from;
}

void Message::SetTo(const std::string& to) {
  m_message[1] = to;
}

void Message::SetText(const std::string& text) {
  m_message[2] = text;
}

void Message::SetMessage(const std::string& from, const std::string& to,
                         const std::string& text) {
  SetFrom(from);
  SetTo(to);
  SetText(text);
}

const std::vector<std::array<std::string, 3>>& Message::GetAllMessages() const {
  return m_all_messages;
}

void Message::SetAllMessages() {
  m_all_messages.push_back(m_message);
}

const void Message::PrintMessage(
    const std::array<std::string, 3> message) const {
  std::cout << message[0] << message[2] << std::endl;
}

const void Message::PrintPrivateMessage(
    const std::array<std::string, 3> message) const {
  std::cout << message[0] << "-> [" << message[1] << "]: " << message[2]
            << std::endl;
}