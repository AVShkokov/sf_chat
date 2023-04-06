#pragma once

#include <array>
#include <string>
#include <vector>

class Message {
 public:
  Message() = default;

  ~Message() = default;

  void SetFrom(const std::string& from);
  void SetTo(const std::string& to);
  void SetText(const std::string& text);

  void SetMessage(const std::string& from, const std::string& to,
                  const std::string& text);

  const std::vector<std::array<std::string, 3>>& GetAllMessages() const;
  void SetAllMessages();

  const void PrintMessage(const std::array<std::string, 3> message) const;
  const void PrintPrivateMessage(
      const std::array<std::string, 3> message) const;

 private:
  std::array<std::string, 3> m_message;

  std::vector<std::array<std::string, 3>> m_all_messages;
};