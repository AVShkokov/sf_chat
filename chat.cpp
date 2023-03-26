#include "chat.h"

#include <iostream>

const void Chat::Init() {
  std::cout << "Welcone to " << GetChatName() << "!" << std::endl;

  char choice;

  do {
    mainMenu();

    std::cin >> choice;

    switch (choice) {
      case '1': {
        newUserMenu();

        break;
      }

      case '2': {
        User user;

        if (loginMenu(user)) {
          createChat(user);
        }

        break;
      }

      case '3': {
        std::cout << std::endl << "Goodbye!" << std::endl;
        break;
      }

      default: {
        std::cout << std::endl << "Input error!" << std::endl;
        break;
      }
    }
  } while (choice != '3');
}

const std::string& Chat::GetChatName() const {
  return m_chat_name;
}

void Chat::SetChatName(std::string& chat_name) {
  m_chat_name = chat_name;
}

const void Chat::mainMenu() {
  std::cout << std::endl;
  std::cout << "Please choose an options:" << std::endl;
  std::cout << "(1) Sign up" << std::endl;
  std::cout << "(2) Sign in" << std::endl;
  std::cout << "(3) Exit" << std::endl;
  std::cout << "_________________________" << std::endl;
  std::cout << std::endl;
  std::cout << "Enter your choice: ";
}

const void Chat::newUserMenu() {
  User user;

  bool isOk = false;

  std::string name;
  std::string login;
  std::string password;

  std::cin.ignore();  // clear buffer, because use mixed input

  std::cout << std::endl;
  std::cout << "Creating new user" << std::endl;
  std::cout << "_________________" << std::endl;
  std::cout << std::endl;

  do {
    std::cout << "Enter name: ";
    std::getline(std::cin, name);
    isOk = user.CheckName(m_users, name);
  } while (!isOk);
  user.SetName(name);

  do {
    std::cout << "Enter login: ";
    std::getline(std::cin, login);
    isOk = user.CheckLogin(m_users, login);
  } while (!isOk);
  user.SetLogin(login);

  do {
    std::cout << "Enter password: ";
    std::getline(std::cin, password);
    isOk = user.CheckPassword(password);
  } while (!isOk);
  user.SetPassword(password);

  if (isOk) {
    m_users.push_back(std::move(user));
  }

  std::cout << "User created successfully!" << std::endl;
}

const bool Chat::loginMenu(User& user) {
  bool isOk = false;

  std::string login;
  std::string password;

  std::cin.ignore();  // clear buffer, because use mixed input

  std::cout << std::endl;
  std::cout << "Sing in to " << GetChatName() << std::endl;
  std::cout << "__________________" << std::endl;
  std::cout << std::endl;

  do {
    std::cout << "Enter your name or login: ";
    std::getline(std::cin, login);

    std::cout << "Enter your password: ";
    std::getline(std::cin, password);

    isOk = user.CheckSingIn(m_users, login, password);
  } while (!isOk);

  for (size_t i = 0; i < m_users.size(); ++i) {
    if (m_users[i].GetName() == login || m_users[i].GetLogin() == login) {
      user = m_users[i];
    }
  }

  std::cout << "Sing in successfully!" << std::endl;

  return true;
}

const void Chat::createChat(const User& user) {
  bool isExit = false;

  std::string message;

  std::cout << std::endl;
  std::cout << "Hello, " << user.GetName() << "!" << std::endl;
  std::cout << "________________________________________" << std::endl;
  std::cout << std::endl;
  std::cout << "[SF_Chat]: " << user.GetName() << " online!" << std::endl;

  while (!isExit) {
    std::cout << "[" << user.GetName() << "]: ";
    getline(std::cin, message);

    if (message == "--exit") {
      std::cout << "[SF_Chat]: " << user.GetName() << " offline!" << std::endl;
      isExit = true;
    }
  }
}
