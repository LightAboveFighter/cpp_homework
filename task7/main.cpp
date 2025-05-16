#include <iostream>

#include "set.h"

int main(int, char**) {
  Set<int> a({1, 2, 3});  // Использует SetListImpl
  Set<int> b({1, 4, 9});
  a.add_elem(4);

  std::cout << a << std::endl;
  // ...
  for (int i = 0; i < 20;
       ++i) {  // При превышении THRESHOLD переключится на SetHashImpl
    a.add_elem(i);
    b.add_elem(i * i);
  }

  std::cout << a << std::endl;
  std::cout << b << std::endl;
  std::cout << a.get_union(b) << std::endl;
  std::cout << a.get_intersection(b) << std::endl;
}
