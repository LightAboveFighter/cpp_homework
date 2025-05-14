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

template <typename Derived>
struct MixInCounter {
  static int counter;
  MixInCounter() { ++counter; }
  ~MixInCounter() { --counter; }

  static int count() { return counter; }
};

template <typename Derived>
int MixInCounter<Derived>::counter = 0;

#endif