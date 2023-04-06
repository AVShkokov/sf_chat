#include "user.h"

#include <iostream>

const std::string& User::GetName() const {
  return m_name;
}

void User::SetName(const std::string& name) {
  m_name = name;
}

const std::string& User::GetLogin() const {
  return m_login;
}

void User::SetLogin(const std::string& login) {
  m_login = login;
}

const std::string& User::GetPassword() const {
  return m_password;
}

void User::SetPassword(const std::string& password) {
  m_password = password;
}

const bool User::CheckName(const std::vector<User>& users,
                           const std::string& name) const {
  return checkSpaces(name) && checkNameUnique(users, name);
}

const bool User::CheckLogin(const std::vector<User>& users,
                            const std::string& login) const {
  return checkSpaces(login) && checkLoginUnique(users, login);
}

const bool User::CheckPassword(const std::string& password) const {
  return checkSpaces(password) && checkPasswordLength(password) &&
         checkPasswordUnique(password);
}

const bool User::checkSpaces(const std::string& str) const {
  if (str.empty()) {
    std::cout << "WARNING: Enter cannot be empty" << std::endl;
    return false;
  }

  for (size_t ch = 0; ch < str.size(); ++ch) {
    if (str[ch] == ' ') {
      std::cout << "WARNING: Enter cannot contain space character" << std::endl;
      return false;
    }
  }

  return true;
}

const bool User::checkNameUnique(const std::vector<User>& users,
                                 const std::string& name) const {
  for (size_t i = 0; i < users.size(); ++i) {
    if (users[i].GetName() == name) {
      std::cout << "WARNING: User with name " << users[i].GetName()
                << " already exists." << std::endl;
      return false;
    }
  }

  return true;
}

const bool User::checkLoginUnique(const std::vector<User>& users,
                                  const std::string& login) const {
  for (size_t i = 0; i < users.size(); ++i) {
    if (users[i].GetLogin() == login) {
      std::cout << "WARNING: User with login " << users[i].GetLogin()
                << " already exists." << std::endl;
      return false;
    }
  }

  return true;
}

const bool User::checkPasswordUnique(const std::string& password) const {
  if (m_name == password) {
    std::cout << "WARNING: Password cannot include your name" << std::endl;
    return false;
  }

  if (m_login == password) {
    std::cout << "WARNING: Password cannot include your login" << std::endl;
    return false;
  }

  return true;
}

const bool User::checkPasswordLength(const std::string& password) const {
  int password_length = 6;
  if (password.size() < password_length) {
    std::cout << "WARNING: Password is too short (must be at less 6 character)"
              << std::endl;
    return false;
  }

  return true;
}

const bool User::CheckSingIn(const std::vector<User>& users,
                             const std::string& login,
                             const std::string& password) const {
  if (users.empty()) {
    return false;
  }

  if (!checkSpaces(login) || !checkSpaces(password)) {
    return false;
  }

  for (size_t i = 0; i < users.size(); ++i) {
    if (users[i].GetLogin() == login && users[i].GetPassword() == password) {
      return true;
    }
  }

  std::cout << "WARNING: Incorrect login or password" << std::endl;
  return false;
}
