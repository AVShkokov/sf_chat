#include "message.h"

#include <iostream>

const std::string& Message::GetFrom() const {
  return m_from;
}

void Message::SetFrom(const std::string& from) {
  m_from = from;
}

const std::string& Message::GetTo() const {
  return m_to;
}

void Message::SetTo(const std::string& to) {
  m_to = to;
}

const std::string& Message::GetText() const {
  return m_text;
}

void Message::SetText(const std::string& text) {
  m_text = text;
}