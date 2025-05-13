#ifndef __USER_H__
#define __USER_H__

#include <iostream>
#include <string>

class Group;

struct User {
  User(std::string name, int id) : _name{name}, _id{id} {}
  User(const User& user) : _name{user._name}, _id{user._id} {}

  ~User() {}

  std::string _name;
  int _id;
  Group* _group;
};

std::ostream& operator<<(std::ostream& os, User& u) {
  os << "User(name=" << u._name << ", id=" << u._id << ")";
  return os;
}

#endif