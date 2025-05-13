#include <chrono>
#include <iostream>
#include <thread>

#include "log.h"

int main(int, char**) {
  using namespace std::chrono_literals;
  Log* l = Singleton<Log>::Instance();

  l->message(LOG_ERROR, "Yeye");

  std::this_thread::sleep_for(1500ms);
  l->message(LOG_WARNING, "OWFBPOFNPWONF");

  std::this_thread::sleep_for(1500ms);
  Singleton<Log>::Instance()->message(LOG_NORMAL, "MMMMMM 12");

  std::this_thread::sleep_for(1500ms);
  l->message(LOG_NORMAL, "MMMM 76");

  Singleton<Log>::Instance()->print();
}
