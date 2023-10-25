#include "user.h"

#include <algorithm>
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

const Hash& User::GetPassword() const {
  return m_password;
}

void User::SetPassword(const Hash& password) {
  m_password = password;
}

bool User::CheckName(const std::vector<User>& users,
                     const std::string& name) const {
  bool isOk = false;
  try {
    isOk = checkSpaces(name);
  }
  catch (const char* exception) {
    std::cout << "Exception caught: " << exception << std::endl;
  }

  return isOk && checkNameUnique(users, name);
}

bool User::CheckLogin(const std::vector<User>& users,
                      const std::string& login) const {
  bool isOk = false;
  try {
    isOk = checkSpaces(login);
  }
  catch (const char* exception) {
    std::cout << "Exception caught: " << exception << std::endl;
  }

  return isOk && checkLoginUnique(users, login);
}

bool User::CheckPassword(const std::string& password) const {
  bool isOk = false;
  try {
    isOk = checkSpaces(password);
  }
  catch (const char* exception) {
    std::cout << "Exception caught: " << exception << std::endl;
  }

  return isOk && checkPasswordLength(password) && checkPasswordUnique(password);
}

bool User::checkSpaces(const std::string& str) const {
  if (str.empty()) {
      throw "Enter cannot be empty";
    }

  if (str.find(' ') != std::string::npos) {
      throw "Enter cannot contain space character";
    }

  return true;
}

bool User::checkNameUnique(const std::vector<User>& users,
                           const std::string& name) const {
  const bool isOk =
      std::any_of(users.begin(), users.end(),
                  [name](const User& user) { return user.GetName() == name; });

  if (isOk) {
      std::cout << "WARNING: User with this name already exists." << std::endl;
      return false;
    }

  return true;
}

bool User::checkLoginUnique(const std::vector<User>& users,
                            const std::string& login) const {
  const bool isOk = std::any_of(
        users.begin(), users.end(),
        [login](const User& user) { return user.GetLogin() == login; });

  if (isOk) {
      std::cout << "WARNING: User with this login already exists." << std::endl;
      return false;
    }

  return true;
}

bool User::checkPasswordUnique(const std::string& password) const {
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

bool User::checkPasswordLength(const std::string& password) const {
  size_t password_length = 6;
  if (password.size() < password_length) {
      std::cout << "WARNING: Password is too short (must be at less 6 character)"
                << std::endl;
      return false;
    }

  return true;
}

bool User::CheckSingIn(const std::vector<User>& users,
		       const std::string& login,
		       const std::string& password) const {
  if (users.empty()) {
      return false;
    }

  bool isOk = false;
  try {
    isOk = !checkSpaces(login) || !checkSpaces(password);
  }
  catch (const char* exception) {
    std::cout << "Exception caught: " << exception << std::endl;
    return isOk;
  }

  Hash passwordHash = sha1(password);

  isOk = std::any_of(
        users.begin(), users.end(), [login, passwordHash](const User& user) {
      return user.GetLogin() == login && user.GetPassword() == passwordHash;
    });

  if (!isOk) {
      std::cout << "WARNING: Incorrect login or password" << std::endl;
      return false;
    }

  return true;
}
