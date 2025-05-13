#ifndef __MIXIN_H__
#define __MIXIN_H__

template <typename Derived>
struct MixInCompOperators {
  bool operator>(Derived const& other) {
    return other < (*static_cast<Derived*>(this));
  }

  bool operator>=(Derived const& other) {
    return !((*static_cast<Derived*>(this)) < other);
  }

  bool operator==(Derived const& other) {
    return !((*static_cast<Derived*>(this)) < other ||
             (*static_cast<Derived*>(this)) > other);
  }

  bool operator!=(Derived const& other) {
    return (*static_cast<Derived*>(this)) < other ||
           (*static_cast<Derived*>(this)) > other;
  }

  bool operator<=(Derived const& other) {
    return !((*static_cast<Derived*>(this)) > other);
  }
};

template <typename T>
static int counter = 0;

template <typename Derived>
struct MixInCounter {
  MixInCounter() { ++counter<Derived>; }

  static int count() { return counter<Derived>; }
};

#endif