#pragma once

#include <string>

class Message {
public:
  Message() = default;
  Message(const std::string& from, const std::string& to,
          const std::string& text)
    : m_from(from), m_to(to), m_text(text) {}

  ~Message() = default;

  const std::string& GetFrom() const;

  const std::string& GetTo() const;

  const std::string& GetText() const;

private:
  std::string m_from;
  std::string m_to;
  std::string m_text;
};
