#include <iostream>
#include <string>

#include "typemap.h"

struct DataA {
  double value;
  //   DataA(std::string str) : value{str} {}
};
struct DataB {
  int value;
};

int main() {
  TypeMap<int, DataA, double, DataB> myTypeMap;
  // Добавление элементов в контейнер
  myTypeMap.add_value<int>(42);
  myTypeMap.add_value<double>(3.14);
  myTypeMap.add_value<DataA>({-10});
  myTypeMap.add_value<DataB>({10});

  std::cout << "Value for int: " << myTypeMap.get_value<int>()
            << std::endl;  // Вывод: 42
  std::cout << "Value for double: " << myTypeMap.get_value<double>()
            << std::endl;  // Вывод: 3.14
  std::cout << "Value for DataA: " << myTypeMap.get_value<DataA>().value
            << std::endl;  // Вывод: Hello, TypeMap!
  std::cout << "Value for DataB: " << myTypeMap.get_value<DataB>().value
            << std::endl;  // Вывод: 10
  // Проверка наличия элемента
  std::cout << "is_contains int? "
            << (myTypeMap.is_contains<int>() ? "Yes" : "No")
            << std::endl;  // Вывод: Yes
  // Удаление элемента
  myTypeMap.delete_value<double>();
  std::cout << "is_contains double? "
            << (myTypeMap.is_contains<double>() ? "Yes" : "No") << std::endl;
  //   // Попытка получения удаленного элемента
  //   std::cout << "Value for double after removal: "
  //             << myTypeMap.get_value<double>()
  //             << std::endl;  // Вывод: (некорректное значение)
}