#include "chat.h"

#include <conio.h>
#include <iomanip>
#include <iostream>

const std::string& Chat::GetChatName() const {
  return m_chat_name;
}

void Chat::SetChatName(const std::string& chat_name) {
  m_chat_name = chat_name;
}

const void Chat::Init() {
  std::cout << "Welcone to " << GetChatName() << "!" << std::endl;

  char choice;

  do {
    mainMenu();

    std::cin >> choice;

    switch (choice) {
      case '1': {
        singUp();
        break;
      }
      case '2': {
        if (singIn()) {
          createChat();
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

const bool Chat::singUp() {
  std::cin.ignore();  // clear buffer, because use mixed input

  std::cout << std::endl;
  std::cout << "Creating new user" << std::endl;
  std::cout << "_________________" << std::endl;
  std::cout << std::endl;
  std::cout << "(3) Exit in main menu" << std::endl;
  std::cout << std::endl;

  bool isOk = false;

  std::string name;
  do {
    std::cout << "Enter name: ";
    std::getline(std::cin, name);

    if (name == "3") {
      return false;
    }

    isOk = m_user.CheckName(m_users, name);
  } while (!isOk);
  m_user.SetName(name);

  std::string login;
  do {
    std::cout << "Enter login: ";
    std::getline(std::cin, login);
    isOk = m_user.CheckLogin(m_users, login);
  } while (!isOk);
  m_user.SetLogin(login);

  std::string password;
  do {
    std::cout << "Enter password: ";
    inputPassword(password);

    isOk = m_user.CheckPassword(password);
  } while (!isOk);
  m_user.SetPassword(password);

  if (isOk) {
    m_users.push_back(m_user);
  }

  std::cout << "User created successfully!" << std::endl;

  return true;
}

const bool Chat::singIn() {
  std::cin.ignore();  // clear buffer, because use mixed input

  std::cout << std::endl;
  std::cout << "Sing in to " << GetChatName() << std::endl;
  std::cout << "__________________" << std::endl;
  std::cout << std::endl;
  std::cout << "(3) Exit in main menu" << std::endl;
  std::cout << std::endl;

  bool isOk = false;

  std::string login;
  std::string password;
  do {
    std::cout << "Enter your login: ";
    std::getline(std::cin, login);

    if (login == "3") {
      return false;
    }

    std::cout << "Enter your password: ";
    inputPassword(password);

    isOk = m_user.CheckSingIn(m_users, login, password);
  } while (!isOk);

  for (const auto& user : m_users) {
    if (user.GetLogin() == login) {
      m_user = user;
    }
  }

  std::cout << "Sing in successfully!" << std::endl;

  return true;
}

void Chat::inputPassword(std::string& password) {
  char ch;
  while ((ch = _getch()) != '\r') {
    password += ch;
    _putch('*');
  }
  std::cout << std::endl;
}

const void Chat::loadHistory(const std::string& user_name) const {
  for (const auto& message : m_messages) {
    if (message.GetTo() != "all" &&
        (message.GetFrom() == user_name || message.GetTo() == user_name)) {
      std::cout << "[" << message.GetFrom() << " to " << message.GetTo()
                << "]:" << message.GetText() << std::endl;
    } else if (message.GetTo() != "all" && (message.GetFrom() != user_name ||
                                            message.GetTo() != user_name)) {
      continue;
    } else {
      std::cout << "[" << message.GetFrom() << "]: " << message.GetText()
                << std::endl;
    }
  }
}

const void Chat::createChat() {
  std::cout << std::endl;
  std::cout << "Hello, " << m_user.GetName() << "!" << std::endl;
  std::cout << "________________________________________" << std::endl;
  std::cout << std::endl;
  std::cout << "Type \"@name\" to send private message" << std::endl;
  std::cout << "Type \"--help\" to show help" << std::endl;
  std::cout << "Type \"--leave\" to exit from chat room" << std::endl;
  std::cout << std::endl;

  std::string from = m_user.GetName();

  if (!m_messages.empty()) {
    loadHistory(from);
  }

  bool isLeave = false;
  while (!isLeave) {
    std::cout << "[" + from + "]: ";

    std::string to = "all";
    std::string text;

    getline(std::cin, text);

    if (text[0] == '-' && text[1] == '-') {
      isLeave = chatCommand(text);
      continue;
    } else if (text[0] == '@') {
      if (!privateMessage(text, to)) {
        continue;
      }
    }

    m_messages.emplace_back(Message(from, to, text));
  }
}

const bool Chat::chatCommand(const std::string& command) const {
  if (command == "--help") {
    std::cout << std::endl;
    std::cout << "_____________________________________" << std::endl;
    std::cout << std::endl;
    std::cout << "--help" << std::setw(14) << "Show help" << std::endl;
    std::cout << "--leave" << std::setw(23) << "Exit from chat room"
              << std::endl;
    std::cout << "--users" << std::setw(18) << "Show all users" << std::endl;
    std::cout << std::endl;

    return false;
  }

  if (command == "--leave") {
    return true;
  }

  if (command == "--users") {
    for (const auto& user : m_users) {
      std::cout << user.GetLogin() << std::endl;
    }

    return false;
  }

  std::cout << "Unknown command. Please type \"--help\" for more information"
            << std::endl;
  return false;
}

const bool Chat::privateMessage(std::string& text, std::string& to) {
  if (text[1] == ' ') {
    std::cout << "WARNING: Enter cannot contain space between @ and name"
              << std::endl;

    return false;
  }

  to.clear();

  int count = 0;

  for (const auto& ch : text) {
    if (ch == ' ') {
      break;
    } else if (ch == '@') {
      continue;
    } else {
      to += ch;
      count += 1;
    }
  }

  bool isFind = false;
  for (const auto& user : m_users) {
    if (user.GetLogin() == to) {
      isFind = true;
    }
  }

  if (!isFind) {
    std::cout
        << "WARNING: User wiht login " << to
        << " is not in user list. Please type \"--users\" for more information"
        << std::endl;

    return false;
  }

  if (m_user.GetLogin() == to) {
    std::cout << "WARNING: You cannot send message to yourself" << std::endl;

    return false;
  }

  if (text.size() < count + 3) {
    std::cout << "WARNING: Message is not typed" << std::endl;

    return false;
  } else {
    text = text.substr(count + 1);
  }

  return true;
}