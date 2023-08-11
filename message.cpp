#include "message.h"

#include <iostream>

const std::string& Message::GetFrom() const {
	return m_from;
}

const std::string& Message::GetTo() const {
	return m_to;
}

const std::string& Message::GetText() const {
	return m_text;
}