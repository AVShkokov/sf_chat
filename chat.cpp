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
        std::cout << std::endl << "Login" << std::endl;
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
