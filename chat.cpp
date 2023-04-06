#include "chat.h"

#include <iomanip>
#include <iostream>

#include <array>

const void Chat::Init() {
  std::cout << "Welcone to " << GetChatName() << "!" << std::endl;

  Message* messages = new Message();

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
        User user;

        if (singIn(user)) {
          createChat(user, messages);
        }

        break;
      }

      case '3': {
        delete messages;
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

void Chat::SetChatName(const std::string& chat_name) {
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

const void Chat::singUp() {
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

const bool Chat::singIn(User& user) {
  bool isOk = false;

  std::string login;
  std::string password;

  std::cin.ignore();  // clear buffer, because use mixed input

  std::cout << std::endl;
  std::cout << "Sing in to " << GetChatName() << std::endl;
  std::cout << "__________________" << std::endl;
  std::cout << std::endl;

  do {
    std::cout << "Enter your login: ";
    std::getline(std::cin, login);

    std::cout << "Enter your password: ";
    std::getline(std::cin, password);

    isOk = user.CheckSingIn(m_users, login, password);
  } while (!isOk);

  for (size_t i = 0; i < m_users.size(); ++i) {
    if (m_users[i].GetLogin() == login) {
      user = m_users[i];
    }
  }

  std::cout << "Sing in successfully!" << std::endl;

  return true;
}

const void Chat::loadHistory(const Message* messages,
                             const std::string& from) const {
  for (size_t i = 0; i < messages->GetAllMessages().size(); ++i) {
    if (messages->GetAllMessages()[i][1] != "all" &&
        messages->GetAllMessages()[i][0] == from) {
      messages->PrintPrivateMessage(messages->GetAllMessages()[i]);
    } else if (messages->GetAllMessages()[i][1] != "all" &&
               messages->GetAllMessages()[i][0] != from) {
      continue;
    } else {
      messages->PrintMessage(messages->GetAllMessages()[i]);
    }
  }
}

const void Chat::createChat(const User& user, Message* messages) {
  bool isLeave = false;

  std::string from = "[" + user.GetName() + "]: ";
  std::string to = "all";
  std::string text;

  std::cout << std::endl;
  std::cout << "Hello, " << user.GetName() << "!" << std::endl;
  std::cout << "________________________________________" << std::endl;
  std::cout << std::endl;
  std::cout << "Type \"@name\" to send private message" << std::endl;
  std::cout << "Type \"--help\" to show help" << std::endl;
  std::cout << "Type \"--leave\" to exit from chat room" << std::endl;
  std::cout << std::endl;

  if (!messages->GetAllMessages().empty()) {
    loadHistory(messages, from);
  }

  while (!isLeave) {
    std::cout << from;
    getline(std::cin, text);

    if (text[0] == '-' && text[1] == '-') {
      isLeave = chatCommand(text);
      continue;
    } else if (text[0] == '@') {
      if (text[1] == ' ') {
        std::cout << "WARNING: Enter cannot contain space between @ and name"
                  << std::endl;
        continue;
      }

      to.clear();

      int count = 0;

      for (size_t i = 1; i < text.size(); ++i) {
        if (text[i] == ' ') {
          break;
        } else {
          to += text[i];
          count += 1;
        }
      }
      if (text.size() < count + 2) {
        std::cout << "WARNING: Message is not typed" << std::endl;
        continue;
      } else {
        text = text.substr(count + 2);
      }
    }

    messages->SetMessage(from, to, text);
    messages->SetAllMessages();
  }
}

const bool Chat::chatCommand(const std::string& message) const {
  if (message == "--help") {
    int width = 20;

    std::cout << std::endl;
    std::cout << "_____________________________________" << std::endl;
    std::cout << std::endl;
    std::cout << "--help" << std::setw(width - 6) << "Show help" << std::endl;
    std::cout << "--leave" << std::setw(width + 3) << "Exit from chat room"
              << std::endl;
    std::cout << "--online" << std::setw(width) << "Show users online"
              << std::endl;
    std::cout << "--users" << std::setw(width - 2) << "Show all users"
              << std::endl;
    std::cout << std::endl;

    return false;
  }

  if (message == "--leave") {
    return true;
  }

  //if (message == "--online") {
  //	return false;
  //}

  if (message == "--users") {
    for (size_t i = 0; i < m_users.size(); ++i) {
      std::cout << m_users[i].GetLogin() << std::endl;
    }

    return false;
  }

  std::cout << "Unknown command. Please type \"--help\" for more information"
            << std::endl;
  return false;
}
