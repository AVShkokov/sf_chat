#include "chat.h"

#include <iomanip>
#include <iostream>

const std::string& Chat::GetChatName() const {
  return m_chat_name;
}

void Chat::SetChatName(const std::string& chat_name) {
  m_chat_name = chat_name;
}

void Chat::Init() {
  loadUsers();

  std::cout << "Welcome to " << GetChatName() << "!" << std::endl;

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

void Chat::loadUsers() {
  users_file = std::fstream(users_file_name, std::ios::in);

  if (!users_file) {
    users_file = std::fstream(users_file_name, std::ios::out | std::ios::trunc);
  }

  if (!users_file.is_open()) {
    std::cout << "Error: Could not open file \"users\"!" << std::endl;

    return;
  }

  std::string name;
  std::string login;
  std::string password;

  while (!users_file.eof()) {
    users_file >> name >> login >> password;

    if (name.empty() || login.empty() || password.empty()) {
      continue;
    }

    m_users.emplace_back(User(name, login, password));

    name.clear();
    login.clear();
    password.clear();
  }

  users_file.close();
}

void Chat::mainMenu() {
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
  users_file.open(users_file_name, std::ios::out | std::ios::app);

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
  users_file << name << " ";

  std::string login;
  do {
    std::cout << "Enter login: ";
    std::getline(std::cin, login);
    isOk = m_user.CheckLogin(m_users, login);
  } while (!isOk);
  m_user.SetLogin(login);
  users_file << login << " ";

  std::string password;
  do {
    std::cout << "Enter password: ";
    std::getline(std::cin, password);
    isOk = m_user.CheckPassword(password);
  } while (!isOk);
  m_user.SetPassword(password);
  users_file << password << std::endl;

  users_file.close();

  m_users.push_back(m_user);

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
    std::getline(std::cin, password);
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

void Chat::loadHistory(const std::string& user_name) {
  messages_file = std::fstream(messages_file_name, std::ios::in);

  if (!messages_file) {
    messages_file =
        std::fstream(messages_file_name, std::ios::out | std::ios::trunc);
  }

  if (!messages_file.is_open()) {
    std::cout << "Error: Could not open file \"messages\"!" << std::endl;

    return;
  }

  std::string str;
  while (std::getline(messages_file, str)) {
    size_t pos = str.find(' ');
    std::string from = str.substr(0, pos);

    pos = str.find(' ', pos + 1);
    std::string to = str.substr(from.size() + 1, pos - (from.size() + 1));

    std::string text = str.erase(0, pos + 1);

    if (from.empty() || to.empty() || text.empty()) {
      continue;
    }

    m_messages.emplace_back(Message(from, to, text));
  }

  messages_file.close();

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

void Chat::createChat() {
  std::cout << std::endl;
  std::cout << "Hello, " << m_user.GetName() << "!" << std::endl;
  std::cout << "________________________________________" << std::endl;
  std::cout << std::endl;
  std::cout << "Type \"@name\" to send private message" << std::endl;
  std::cout << "Type \"--help\" to show help" << std::endl;
  std::cout << "Type \"--leave\" to exit from chat room" << std::endl;
  std::cout << std::endl;

  const std::string from = m_user.GetName();

  loadHistory(from);

  messages_file.open(messages_file_name, std::ios::out | std::ios::app);

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
    messages_file << from << " " << to << " " << text << std::endl;
  }

  messages_file.close();
}

const bool Chat::chatCommand(const std::string& command) const {
  if (command == "--help") {
    std::cout << std::endl;
    std::cout << "_____________________________________" << std::endl;
    std::cout << std::endl;
    std::cout << "--users" << std::setw(18) << "Show all users" << std::endl;
    std::cout << "--help" << std::setw(14) << "Show help" << std::endl;
    std::cout << "--leave" << std::setw(23) << "Exit from chat room"
              << std::endl;
    std::cout << std::endl;

    return false;
  }

  if (command == "--leave") {
    return true;
  }

  if (command == "--users") {
    for (const auto& user : m_users) {
      std::cout << "User name: " << user.GetName() << std::endl;
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

  size_t count = 0;

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
    if (user.GetName() == to) {
      isFind = true;
    }
  }

  if (!isFind) {
    std::cout
        << "WARNING: User with name " << to
        << " is not in user list. Please type \"--users\" for more information"
        << std::endl;

    return false;
  }

  if (m_user.GetName() == to) {
    std::cout << "WARNING: You cannot send message to yourself" << std::endl;

    return false;
  }

  size_t pos = text.find(' ');
  if (text[pos + 1] == ' ') {
    std::cout << "WARNING: Enter cannot contain two or more space between name "
                 "and message"
              << std::endl;

    return false;
  }

  if (text.size() < count + 2) {
    std::cout << "WARNING: Message is not typed" << std::endl;

    return false;
  } else {
    text = text.substr(count + 1);
  }

  return true;
}
