#include "user.h"

#include <algorithm>

const QString& User::GetName() const {
  return m_name;
}

void User::SetName(const QString& name) {
  m_name = name;
}

const QString& User::GetLogin() const {
  return m_login;
}

void User::SetLogin(const QString& login) {
  m_login = login;
}

const Hash& User::GetPassword() const {
  return m_password;
}

void User::SetPassword(const Hash& password) {
  m_password = password;
}

bool User::CheckName(const QVector<User>& users,
                     const QString& name,
                     QString& message) const {
  bool isOk = false;

  isOk = checkSpaces(name, message);
  if(!isOk) {
      return isOk;
    }

  return isOk && checkNameUnique(users, name, message);
}

bool User::CheckLogin(const QVector<User>& users,
                      const QString& login,
                      QString& message) const {
  bool isOk = false;

  isOk = checkSpaces(login, message);
  if(!isOk) {
      return isOk;
    }

  return isOk && checkLoginUnique(users, login, message);
}

bool User::CheckPassword(const QString& password,
                         QString& message) const {
  bool isOk = false;

  isOk = checkSpaces(password, message);
  if(!isOk) {
      return isOk;
    }

  return isOk && checkPasswordLength(password, message) && checkPasswordUnique(password, message);
}

bool User::checkSpaces(const QString& str, QString& message) const {
  if (str.isEmpty()) {
      message = "Enter cannot be empty";

      return false;
    }

  if (str.contains(' ')) {
      message = "Enter cannot contain space character";

      return false;
    }

  return true;
}

bool User::checkNameUnique(const QVector<User>& users,
                           const QString& name,
                           QString& message) const {
  const bool isOk =
      std::any_of(users.begin(), users.end(),
                  [name](const User& user) { return user.GetName() == name; });

  if (isOk) {
      message = "User with this name already exists.";
      return false;
    }

  return true;
}

bool User::checkLoginUnique(const QVector<User>& users,
                            const QString& login,
                            QString& message) const {
  const bool isOk = std::any_of(
        users.begin(), users.end(),
        [login](const User& user) { return user.GetLogin() == login; });

  if (isOk) {
      message = "User with this login already exists.";
      return false;
    }

  return true;
}

bool User::checkPasswordUnique(const QString& password,
                               QString& message) const {
  if (m_name == password) {
      message = "Password cannot include your name";
      return false;
    }

  if (m_login == password) {
      message = "Password cannot include your login";
      return false;
    }

  return true;
}

bool User::checkPasswordLength(const QString& password,
                               QString& message) const {
  int password_length = 6;
  if (password.size() < password_length) {
      message = "Password is too short (must be at less 6 character)";
      return false;
    }

  return true;
}

bool User::CheckSingIn(const QVector<User>& users,
		       const QString& login,
		       const QString& password,
		       QString& message) const {
  if (users.empty()) {
      message = "Users list is empty. Please register.";
      return false;
    }

  bool isOk = false;

  isOk = checkSpaces(login, message);
  if(!isOk) {
      return isOk;
    }

  isOk = checkSpaces(password, message);
  if(!isOk) {
      return isOk;
    }

  Hash passwordHash = sha1(password.toStdString());

  isOk = std::any_of(
        users.begin(), users.end(), [login, passwordHash](const User& user) {
      return user.GetLogin() == login && user.GetPassword() == passwordHash;
    });

  if (!isOk) {
      message = "Incorrect login or password";
      return false;
    }

  return true;
}
