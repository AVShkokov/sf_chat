#pragma once

#include <QString>
#include <QVector>

#include "sha1.h"

class User {
public:
  User() = default;
  User(const QString& name, const QString& login,
       const Hash& password, const int ban_status)
    : m_name(name), m_login(login), m_password(password), m_ban_status(ban_status) {}

  ~User() = default;

  const QString& GetName() const;
  void SetName(const QString& name);
  bool CheckName(const QVector<User>& users,
                 const QString& name,
                 QString& message) const;

  const QString& GetLogin() const;
  void SetLogin(const QString& login);
  bool CheckLogin(const QVector<User>& users,
                  const QString& login,
                  QString& message) const;

  void SetPassword(const Hash& password);
  bool CheckPassword(const QString& password,
                     QString& message) const;

  // This is method here because method GetPassword is protected
  bool CheckSingIn(const QVector<User>& users,
                   const QString& login,
                   const QString& password,
                   QString& message) const;

  int GetBanStatus() const;
  void SetBanStatus(const int& ban_status);

  int GetOnlineStatus() const;
  void SetOnlineStatus(const int& online_status);

protected:
  const Hash& GetPassword() const;

private:
  QString m_name;
  QString m_login;
  Hash m_password;
  int m_ban_status;
  int m_online_status;

  bool checkSpaces(const QString& str, QString& message) const;

  bool checkPasswordLength(const QString& password,
                           QString& message) const;

  bool checkNameUnique(const QVector<User>& users,
                       const QString& name,
                       QString& message) const;
  bool checkLoginUnique(const QVector<User>& users,
                        const QString& login,
                        QString& message) const;
  bool checkPasswordUnique(const QString& password,
                           QString& message) const;
};
