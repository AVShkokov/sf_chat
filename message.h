#pragma once

#include <vector>
#include <string>

class Message {
  public:
	Message() = default;
	
	~Message() = default;
	
	const std::vector<std::string>& GetMessages() const;
	void SetMessage(const std::string message);
	
  private:
  	std::vector<std::string> m_messages;
};