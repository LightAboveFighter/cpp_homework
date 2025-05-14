#ifndef __GROUP_H__
#define __GROUP_H__

#include <algorithm>
#include <initializer_list>
#include <iostream>
#include <list>

#include "user.h"

struct Group {
  Group(int id) : _id{id} {}

  void addUser(const User& u) {
    // Сохраняем копию объекта, чтобы избежать висячих указателей
    User* u2 = new User(u);
    u2->_group = this;
    _members.push_back(u2);  // Создаём новый объект в куче
  }

  std::list<User*>::iterator findUser(int id) {
    return std::find_if(_members.begin(), _members.end(),
                        [&id](User* u) { return u->_id == id; });
  }

  ~Group() { deleteGroup(); }

  void deleteGroup() {
    for (const auto* user : _members) {
      delete user;
    }
    _members.clear();
  }

  void getUser(int id) const {  // Метод не изменяет объект -> const
    auto iter = std::find_if(_members.begin(), _members.end(),
                             [&id](User* u) { return u->_id == id; });
    if (iter != _members.end() && *iter != nullptr) {
      std::cout << **iter << std::endl;
    }
  }

  void deleteUser(int id) {
    auto iter = findUser(id);
    if (iter != _members.end()) {
      User* user = *iter;  // Сохраняем указатель перед удалением из списка
      _members.erase(iter);
      delete user;  // Освобождаем память
    }
  }

  int _id;
  std::list<User*> _members{};
};

// Исправленный оператор вывода с константной ссылкой
std::ostream& operator<<(std::ostream& os, const Group& g) {
  os << "Group(users={" << std::endl;
  for (auto user : g._members) {
    os << "\t" << *user << "," << std::endl;
  }
  os << "}, "
     << "id=" << g._id << ")";
  return os;
}

#endif