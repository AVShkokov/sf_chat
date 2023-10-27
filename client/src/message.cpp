#include "message.h"

const QString& Message::GetFrom() const {
  return m_from;
}

const QString& Message::GetTo() const {
  return m_to;
}

const QString& Message::GetText() const {
  return m_text;
}
