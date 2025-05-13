#include <iostream>
#include <typeinfo>

#include "typelist.h"

int main() {
  using EmptyList = TypeList<>;
  using List1 = PushFront<EmptyList, int>;
  using List2 = PushBack<List1, char>;
  using List3 = PushFront<List2, double>;

  // Проверка размера
  static_assert(Size<EmptyList> == 0);
  static_assert(Size<List1> == 1);
  static_assert(Size<List2> == 2);
  static_assert(Size<List3> == 3);

  // Проверка Get
  static_assert(std::is_same_v<Get<List1, 0>, int>);
  static_assert(std::is_same_v<Get<List2, 1>, char>);
  static_assert(std::is_same_v<Get<List3, 0>, double>);

  // Проверка Contains
  static_assert(Contains<List2, int> == true);
  static_assert(Contains<List2, double> == false);
  static_assert(Contains<List3, char> == true);

  // Проверка IndexOf
  static_assert(IndexOf<List2, int> == 0);
  static_assert(IndexOf<List2, char> == 1);
  static_assert(IndexOf<List3, double> == 0);
  static_assert(IndexOf<List3, char> == 2);
}