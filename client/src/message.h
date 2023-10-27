#pragma once

#include <QString>

class Message {
public:
  Message() = default;
  Message(const QString& from, const QString& to,
          const QString& text)
    : m_from(from), m_to(to), m_text(text) {}

  ~Message() = default;

  const QString& GetFrom() const;

  const QString& GetTo() const;

  const QString& GetText() const;

private:
  QString m_from;
  QString m_to;
  QString m_text;
};
