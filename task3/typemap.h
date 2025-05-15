#ifndef __TYPEMAP_H__
#define __TYPEMAP_H__

#include "typelist.h"

namespace __TypeMap_inner__ {

struct node_outer {
  node_outer* next{nullptr};
  bool is_set{false};

  virtual void get_data(void* _data) = 0;
  virtual void set_data(const void* _data) = 0;
  virtual ~node_outer() = default;
};

template <typename T1, typename... T2>
struct node;

template <typename T, typename... T2>
struct node : node_outer {
  node() {
    if constexpr (sizeof...(T2) > 0) {
      next = new node<T2...>();
    } else {
      next = nullptr;
    }
  }

  T data{};
  virtual void get_data(void* _data) override {
    *static_cast<T*>(_data) = data;
  }
  virtual void set_data(const void* _data) override {
    is_set = true;
    data = *static_cast<const T*>(_data);
  }
};

};  // namespace __TypeMap_inner__

template <typename... T>
class TypeMap {
  using Keys = TypeList<T...>;
  using node_outer = typename __TypeMap_inner__::node_outer;

  template <typename... Types>
  using node = typename __TypeMap_inner__::node<Types...>;

 public:
  TypeMap() {
    start = new node<T...>();
    node_outer* iter = start;
    node_outer* buffer;
  }

  ~TypeMap() {
    node_outer* next;
    for (int i = 0; i < size(); ++i) {
      next = start->next;
      delete start;
      start = next;
    }
    delete start;
  }

  template <typename Type>
  void add_value(const Type& value) {
    node_outer* n = get_node<Type>();
    static_cast<node<Type>*>(n)->set_data(&value);
  }

  template <typename Type>
  Type get_value() {
    node_outer* n = get_node<Type>();
    if (n->is_set) {
      Type ret;
      static_cast<node<Type>*>(n)->get_data(&ret);
      return ret;
    }
    throw std::runtime_error("Attempt of getting deleted element");
  }

  template <typename Type>
  void delete_value() {
    get_node<Type>()->is_set = false;
  }

  template <typename Type>
  const bool is_contains() const {
    return get_node<Type>()->is_set;
  }

  constexpr size_t size() const { return Size<Keys>; }

 private:
  node_outer* start;

  template <typename Type>
  node_outer* get_node() const {
    node_outer* iter = start;
    for (int i = 0; i < IndexOf<Keys, Type>; ++i) {
      iter = iter->next;
    }
    return iter;
  }
};

#endif