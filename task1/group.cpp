#include "group.h"

#include "user.h"

void Group::addUser(
    User* u) {  // переделать и сделать уникальность пользователя
  u->_group = this;
  _members.push_back(u);
}

std::list<User*>::iterator Group::findUser(int id) {
  return std::find_if(_members.begin(), _members.end(),
                      [&id](User* u) { return u->_id == id; });
}

void Group::deleteGroup() {
  _members.clear();
}

void Group::getUser(int id) const {
  auto iter = std::find_if(_members.begin(), _members.end(),
                           [&id](User* u) { return u->_id == id; });
  if (iter != _members.end() && *iter != nullptr) {
    std::cout << **iter << std::endl;
  }
}

void Group::deleteUser(int id) {
  auto iter = findUser(id);
  if (iter != _members.end()) {
    (*iter)->_group = nullptr;
    _members.erase(iter);
  }
}

std::ostream& operator<<(std::ostream& os, const Group& g) {
  os << "Group(users={" << std::endl;
  for (auto user : g._members) {
    os << "\t" << *user << "," << std::endl;
  }
  os << "}, "
     << "id=" << g._id << ")";
  return os;
}