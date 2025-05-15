#ifndef __LOG_H__
#define __LOG_H__

#include <ctime>
#include <iostream>
#include <list>
#include <string>

template <typename Derived>
class Singleton {
 public:
  Singleton(Singleton& other) = delete;
  Singleton() {}

  void operator=(const Singleton&) = delete;

  template <typename... T>
  static Derived* Instance(T... args) {
    static Derived* object = new Derived(args...);
    return object;
  }
};

enum LogLevel { LOG_NORMAL = 0, LOG_WARNING, LOG_ERROR };

inline const std::string get_level_string(LogLevel& level) {
  switch (level) {
    case LOG_NORMAL:
      return "LOG_NORMAL ";
      break;
    case LOG_WARNING:
      return "LOG_WARNING";
      break;
    case LOG_ERROR:
      return "LOG_ERROR  ";
      break;
  }
  return "";
}

class Log : public Singleton<Log> {
 public:
  struct Message {
    std::time_t time;
    const std::string message;
    LogLevel level;

    Message(std::time_t _time, const std::string _message, LogLevel _level)
        : time{_time}, message{_message}, level{_level} {}

    std::string to_string() {
      std::string str_time = std::string(std::asctime(std::localtime(&time)));
      str_time.pop_back();
      return "[" + str_time + "][" + get_level_string(level) + "]: " + message +
             "\n";
    }
  };

  void message(LogLevel level, const std::string text) {
    messages.push_back(new Message(std::time(nullptr), text, level));
  }

  void print() {
    for (Message* const mes : messages) {
      std::cout << (*mes).to_string();
    }
  }

  ~Log() {
    for (const Message* mes : messages) {
      delete mes;
    }
    messages.clear();
  }

 private:
  std::list<Message*> messages;
};

#endif