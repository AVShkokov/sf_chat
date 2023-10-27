#include "logger.h"

#include <iostream>
#include <vector>

Logger::Logger(const std::string& file_name) : m_file_name(file_name) {
  m_file = std::fstream(m_file_name, std::ios::app);

  if (!m_file) {
      m_file = std::fstream(m_file_name, std::ios::out | std::ios::trunc);
    }

  if (!m_file.is_open()) {
      std::cout << "Error: Could not open file \"" << m_file_name << "\"!" << std::endl;
    }
}

Logger::~Logger() {
  m_file.close();
}

void Logger::WriteToLogFile(const std::string& log_text)
{
  m_mutex.lock();

  m_file.open(m_file_name, std::ios_base::in | std::ios_base::out);

  if (m_file.is_open())
    {
      m_file.seekp(0, std::ios_base::end);
      m_file << log_text << std::endl;
    }
  else
    {
      std::cout << "Error: Could not open file \"" << m_file_name << "\"!" << std::endl;
    }

  m_file.close();

  m_mutex.unlock();
}

void Logger::ReadFromLogFile()
{
  m_mutex.lock_shared();

  std::vector<std::string> result;

  m_file.open(m_file_name, std::ios_base::in | std::ios_base::out);

  if (m_file.is_open())
    {
      m_file.seekg(0, std::ios_base::beg);

      std::string str;
      while (std::getline(m_file, str))
        {
          result.push_back(str);
        }
    }
  else
    {
      std::cout << "Error: Could not open file \"" << m_file_name << "\"!" << std::endl;
    }

  m_file.close();

  if (result.empty()) {
      std::cout << "Log is empty" << std::endl;
    }
  else {
      std::cout << result.back() << std::endl;
    }

  m_mutex.unlock_shared();
}
