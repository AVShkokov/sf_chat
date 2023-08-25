#pragma once

#include "message.h"
#include "user.h"
#include "database.h"
#include "logger.h"

#include <string>
#include <vector>
#include <memory>

class Chat {
public:
	Chat() = default;
	explicit Chat(const std::string& chat_name) : m_chat_name(chat_name) {}

	~Chat() = default;

	const std::string& GetChatName() const;

	void Init();

private:
	std::string m_chat_name;

	User m_user;
	std::vector<User> m_users;
	std::vector<Message> m_messages;

	std::shared_ptr<DataBase> m_database = std::make_shared<DataBase>();

	const std::string m_log_file_name = "log.txt";
	Logger* m_log = new Logger(m_log_file_name);

	void readFromDB(const bool& isUsers);

	void mainMenu();

	const bool singUp();
	const bool singIn();

	void loadHistory(const std::string& user_name);

	void createChat();

	const bool privateMessage(std::string& text, std::string& to);

	const bool chatCommand(const std::string& command) const;
};
