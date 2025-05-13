#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "group.h"
#include "user.h"

std::list<Group*> groups;
std::list<User*> users;

std::list<Group*>::iterator findGroup(int id) {
  return std::find_if(groups.begin(), groups.end(),
                      [&id](Group* g) { return g->_id == id; });
}

std::list<User*>::iterator findUser(int id) {
  return std::find_if(users.begin(), users.end(),
                      [&id](User* u) { return u->_id == id; });
}

void getGroup(int id) {
  auto target = findGroup(id);
  if (target == groups.end()) {
    std::cout << "Group with id=" << id << " is not found" << std::endl;
    return;
  }
  std::cout << **target << std::endl;
}

void deleteGroup(int id) {
  auto target = findGroup(id);
  if (target == groups.end()) {
    std::cout << "Group with id=" << id << " is not found" << std::endl;
    return;
  }
  groups.erase(target);
}

void createGroup(int id) { groups.push_back(new Group(id)); }

void allGroups() {
  std::cout << std::endl;
  for (auto group : groups) {
    std::cout << *group << std::endl;
  }
  std::cout << std::endl;
}

void allUsers() {
  std::cout << std::endl;
  for (auto user : users) {
    std::cout << *user << std::endl;
  }
  std::cout << std::endl;
}

void getUser(int id) {
  auto target = findUser(id);
  if (target == users.end()) {
    std::cout << "User with id=" << id << " is not found" << std::endl;
    return;
  }
  std::cout << **target << std::endl;
}

void deleteUser(int id) {
  auto target = findUser(id);
  if (target == users.end()) {
    std::cout << "User with id=" << id << " is not found" << std::endl;
    return;
  }
  users.erase(target);
}

void createUser(const std::string& name, int id) {
  users.push_back(new User(name, id));
}

// Объявления "реализованных" функций
std::vector<std::string> split(const std::string& s) {
  std::vector<std::string> tokens;
  std::istringstream iss(s);
  std::string token;
  while (iss >> token) {
    tokens.push_back(token);
  }
  return tokens;
}

std::string join(const std::vector<std::string>& parts, size_t start,
                 const std::string& delimiter) {
  if (start >= parts.size()) return "";

  std::string result = parts[start];
  for (size_t i = start + 1; i < parts.size(); ++i) {
    result += delimiter + parts[i];
  }
  return result;
}

void processCommand(const std::vector<std::string>& tokens) {
  if (tokens.empty()) return;

  const std::string& command = tokens[0];

  if (command == "createUser") {
    if (tokens.size() < 2) {
      std::cerr << "Invalid command format for createUser\n";
      return;
    }
    createUser(tokens[1], std::stoi(tokens[2]));
  } else if (command == "deleteUser") {
    if (tokens.size() != 2) {
      std::cerr << "Invalid command format for deleteUser\n";
      return;
    }
    deleteUser(std::stoi(tokens[1]));
  } else if (command == "allUsers") {
    if (tokens.size() != 1) {
      std::cerr << "Invalid command format for allUsers\n";
      return;
    }
    allUsers();
  } else if (command == "getUser") {
    if (tokens.size() != 2) {
      std::cerr << "Invalid command format for getUser\n";
      return;
    }
    getUser(std::stoi(tokens[1]));
  } else if (command == "createGroup") {
    if (tokens.size() != 2) {
      std::cerr << "Invalid command format for createGroup\n";
      return;
    }
    createGroup(std::stoi(tokens[1]));
  } else if (command == "deleteGroup") {
    if (tokens.size() != 2) {
      std::cerr << "Invalid command format for deleteGroup\n";
      return;
    }
    deleteGroup(std::stoi(tokens[1]));
  } else if (command == "allGroups") {
    if (tokens.size() != 1) {
      std::cerr << "Invalid command format for allGroups\n";
      return;
    }
    allGroups();
  } else if (command == "getGroup") {
    if (tokens.size() != 2) {
      std::cerr << "Invalid command format for getGroup\n";
      return;
    }
    getGroup(std::stoi(tokens[1]));
  } else {
    std::cerr << "Unknown command: " << command << "\n";
  }
}

int main() {
  std::string line;
  while (std::getline(std::cin, line)) {
    line.erase(line.begin(), find_if(line.begin(), line.end(),
                                     [](int ch) { return !std::isspace(ch); }));
    line.erase(find_if(line.rbegin(), line.rend(),
                       [](int ch) { return !std::isspace(ch); })
                   .base(),
               line.end());

    if (line.empty()) {
      continue;
    }

    std::vector<std::string> tokens = split(line);
    processCommand(tokens);
  }

  return 0;
}