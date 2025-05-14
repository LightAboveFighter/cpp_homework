#ifndef __BUILDERS_H__
#define __BUILDERS_H__

#include <string>

struct CP {
  std::string name;
  double shir;
  double dolg;
  double penalty;

  CP(const std::string& _name, double _shir, double _dolg, double _penalty)
      : name{_name}, shir{_shir}, dolg{_dolg}, penalty{_penalty} {}

  std::string str_val{"CP"};

  std::string to_string() { return str_val; }
};

class Builder {
 public:
  virtual ~Builder() {}
  virtual void ProducePartA() const = 0;
  virtual void ProducePartB() const = 0;
  virtual void ProducePartC() const = 0;
  virtual double ProducePartD() const = 0;
};

class ConcreteBuilder : Builder {
 public:
  ConcreteBuilder() {}

  void SetProduct(CP* cp) { product = cp; }

  ~ConcreteBuilder() { delete product; }

  virtual void ProducePartA() const override {
    product->str_val += " name=" + product->name + std::string(", ");
  };
  virtual void ProducePartB() const override {
    product->str_val += std::string(" coord={") +
                        std::to_string(product->shir) + std::string("shir, ") +
                        std::to_string(product->dolg) + std::string("dolg}, ");
  };
  virtual void ProducePartC() const override {
    std::string penalty = product->penalty == -1
                              ? "Незачет СУ"
                              : std::to_string(product->penalty);
    product->str_val += std::string(" penalty=") + penalty + std::string(" ");
  };

  virtual double ProducePartD() const {
    if (product->penalty == -1) {
      return 0.;
    }
    return product->penalty;
  }

 private:
  CP* product;
};

#endif