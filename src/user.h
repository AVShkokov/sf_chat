#pragma once

#include <string>
#include <vector>

class User {
public:
  User() = default;
  User(const std::string& name, const std::string& login,
       const std::string& password)
    : m_name(name), m_login(login), m_password(password) {}

  ~User() = default;

  const std::string& GetName() const;
  void SetName(const std::string& name);
  const bool CheckName(const std::vector<User>& users,
                       const std::string& name) const;

  const std::string& GetLogin() const;
  void SetLogin(const std::string& login);
  const bool CheckLogin(const std::vector<User>& users,
                        const std::string& login) const;

  void SetPassword(const std::string& password);
  const bool CheckPassword(const std::string& password) const;

  // This is method here because method GetPassword is protected
  const bool CheckSingIn(const std::vector<User>& users,
                         const std::string& login,
                         const std::string& password) const;

protected:
  const std::string& GetPassword() const;

private:
  std::string m_name;
  std::string m_login;
  std::string m_password;

  const bool checkSpaces(const std::string& str) const;
  const bool checkPasswordLength(const std::string& password) const;

  const bool checkNameUnique(const std::vector<User>& users,
                             const std::string& name) const;
  const bool checkLoginUnique(const std::vector<User>& users,
                              const std::string& login) const;
  const bool checkPasswordUnique(const std::string& password) const;
};
