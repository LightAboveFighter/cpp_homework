#include <iostream>

#include "set.h"

int main(int, char**) {
  Set<int> a({1, 2, 3});  // Использует SetListImpl
  a.add_elem(4);

  std::cout << a << std::endl;
  // ...
  for (int i = 0; i < 20;
       ++i) {  // При превышении THRESHOLD переключится на SetHashImpl
    a.add_elem(i);
  }

  std::cout << a << std::endl;
}
