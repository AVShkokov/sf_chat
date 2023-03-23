#include "user.h"

const std::string& User::GetName() const
{
    return m_name;
}

void User::SetName(const std::string& name)
{
    m_name = name;
}

const std::string& User::GetLogin() const
{
    return m_login;
}

void User::SetLogin(const std::string& login)
{
    m_login = login;
}

const std::string& User::GetPassword() const
{
    return m_password;
}

void User::SetPassword(const std::string& password)
{
    m_password = password;
}