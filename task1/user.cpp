#include "user.h"

#include "group.h"

User::~User() {
  if (_group == nullptr) {
    return;
  }
  _group->deleteUser(_id);
}

std::ostream& operator<<(std::ostream& os, User& u) {
  os << "User(name=" << u._name << ", id=" << u._id << ", group_id=";
  if (u._group != nullptr) {
    os << u._group->_id;
  } else {
    os << "NULL";
  }
  os << ")";
  return os;
}
