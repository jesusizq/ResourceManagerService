#ifndef LOGGER_H
#define LOGGER_H

#include <sstream>
#include <string>

class Logger {
public:
  enum class LogLevel { INFO, WARNING, ERROR, DEBUG, TRACE };

  static void log(std::string_view message, LogLevel level = LogLevel::INFO);

private:
  static std::string getCurrentTime();
  static std::ostream &getStream(LogLevel level);
  static std::string logLevelToString(LogLevel level);
};

#endif // LOGGER_H
