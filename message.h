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
  void SetFrom(const std::string& from);

  const std::string& GetTo() const;
  void SetTo(const std::string& to);

  const std::string& GetText() const;
  void SetText(const std::string& text);

 private:
  std::string m_from;
  std::string m_to;
  std::string m_text;
};