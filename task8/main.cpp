#include <iostream>

#include "arithm.h"

int main(int, char **) {
  ExpressionFactory factory;
  auto c = factory.createConstant(2);
  auto v = factory.createVariable("x");
  auto expr =
      std::make_shared<Addition>(std::make_shared<Multiplying>(c, v), c);
  std::map<std::string, double> context{{"x", 3}};
  std::cout << expr->to_string() << std::endl;
  std::cout << expr->to_string(&context) << std::endl;
  std::cout << expr->calculate(context) << std::endl;
}
