#pragma once

#include <string>
#include <fstream>
#include <shared_mutex>

class Logger
{
public:
	explicit Logger(const std::string& file_name);

	~Logger();

	void WritoToLogFile(const std::string& log_text);
	void ReadFromLogFile();

private:
	std::fstream m_file;
	std::string m_file_name;
	std::shared_mutex m_mutex;
};

