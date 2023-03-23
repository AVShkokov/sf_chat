#pragma once

#include <string>

class User {
 public:
  User() = default;
  User(std::string name, std::string login, std::string password)
      : m_name(name), m_login(login), m_password(password) {}

  ~User() = default;

  const std::string& GetName() const;
  void SetName(const std::string& name);

  const std::string& GetLogin() const;
  void SetLogin(const std::string& login);

protected:
  const std::string& GetPassword() const;
  void SetPassword(const std::string& password);

 private:
  std::string m_name;
  std::string m_login;
  std::string m_password;
};