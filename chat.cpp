#include "chat.h"

#include <iostream>

const void Chat::Init() const {
  std::cout << "Welcone to " << GetChatName() << "!" << std::endl;

  char choice;

  do {
    mainMenu();

    std::cin >> choice;

    switch (choice) {
      case '1': {
        std::cout << std::endl << "Create new user" << std::endl;
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

const void Chat::mainMenu() const {
  std::cout << "___________________________" << std::endl;
  std::cout << "Please choose an options:" << std::endl;
  std::cout << "(1) Sign up" << std::endl;
  std::cout << "(2) Sign in" << std::endl;
  std::cout << "(3) Exit" << std::endl;
  std::cout << "___________________________" << std::endl;
  std::cout << std::endl;
  std::cout << "Enter your choice: ";
}