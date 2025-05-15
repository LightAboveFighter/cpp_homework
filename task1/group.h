#ifndef __GROUP_H__
#define __GROUP_H__

#include <algorithm>
#include <initializer_list>
#include <iostream>
#include <list>

struct User;

struct Group {
  Group(int id) : _id{id} {}

  void addUser(User* u);

  std::list<User*>::iterator findUser(int id);

  ~Group() { deleteGroup(); }

  void deleteGroup();

  void getUser(int id) const;

  void deleteUser(int id);

  int _id;
  std::list<User*> _members{};
};

std::ostream& operator<<(std::ostream& os, const Group& g);

#endif