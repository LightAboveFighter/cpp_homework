#include <iostream>
#include <list>

#include "builders.h"

int main(int, char**) {
  std::list<CP*> cps;
  cps.push_back(new CP("Name1", 12.5, 160.3, -1));
  cps.push_back(new CP("Name345", 0, -60.9, 50));
  cps.push_back(new CP("Alex", -100.1, 90, 14));
  cps.push_back(new CP("Karllarlalr", 63, 14.4, 2));
  cps.push_back(new CP("Dimensional", 27.846, 2, -1));

  ConcreteBuilder* cb = new ConcreteBuilder();
  double pen = 0;
  for (CP* cp : cps) {
    cb->SetProduct(cp);
    cb->ProducePartA();
    cb->ProducePartB();
    cb->ProducePartC();
    std::cout << cp->str_val << std::endl;
    pen += cb->ProducePartD();
  }
  std::cout << "Sum penalty is " << pen << std::endl;
}
