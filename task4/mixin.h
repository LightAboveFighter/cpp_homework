#ifndef __MIXIN_H__
#define __MIXIN_H__

template <typename Derived>
struct MixInCompOperators {
  bool operator>(Derived const& other) const {
    return other < (*static_cast<const Derived*>(this));
  }

  bool operator>=(Derived const& other) const {
    return !(other > (*static_cast<const Derived*>(this)));
  }

  bool operator==(Derived const& other) const {
    return !((*static_cast<const Derived*>(this)) < other ||
             (*static_cast<const Derived*>(this)) > other);
  }

  bool operator!=(Derived const& other) const {
    return (*static_cast<const Derived*>(this)) < other ||
           (*static_cast<const Derived*>(this)) > other;
  }

  bool operator<=(Derived const& other) const {
    return !((*static_cast<const Derived*>(this)) > other);
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