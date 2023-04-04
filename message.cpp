#include "message.h"

const std::vector<std::string>& Message::GetMessages() const {
	return m_messages;
}

void Message::SetMessage(const std::string message) {
	m_messages.push_back(message);
}