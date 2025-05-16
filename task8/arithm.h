#pragma once

#include <cmath>
#include <list>
#include <map>
#include <memory>
#include <string>
#include <unordered_map>

class ExpressionFactory;  // Forward declaration

struct Expression {
  virtual double calculate(std::map<std::string, double> const& context) = 0;
  virtual std::string to_string(
      std::map<std::string, double> const* context) = 0;
};

struct Constant : public Expression {
  Constant(double value) : Expression(), _value(value) {}

  double calculate(std::map<std::string, double> const&) override {
    return _value;
  }

  std::string to_string(std::map<std::string, double> const*) override {
    return std::to_string(_value);
  }

 private:
  const double _value;
};

struct Variable : public Expression {
  Variable(std::string name) : _name(std::move(name)) {}

  double calculate(std::map<std::string, double> const& context) override {
    return context.at(_name);
  }

  std::string to_string(
      std::map<std::string, double> const* context = nullptr) override {
    if (context) {
      return std::to_string(context->at(_name));
    }
    return _name;
  }

 private:
  const std::string _name;
};

struct ExpressionOperator : public Expression {
  ExpressionOperator(std::shared_ptr<Expression> expr1,
                     std::shared_ptr<Expression> expr2)
      : _expr1(std::move(expr1)), _expr2(std::move(expr2)) {}

 protected:
  std::shared_ptr<Expression> _expr1;
  std::shared_ptr<Expression> _expr2;
};

struct Addition : public ExpressionOperator {
  using ExpressionOperator::ExpressionOperator;

  double calculate(std::map<std::string, double> const& context) override {
    return _expr1->calculate(context) + _expr2->calculate(context);
  }

  std::string to_string(
      std::map<std::string, double> const* context = nullptr) override {
    return _expr1->to_string(context) + "+" + _expr2->to_string(context);
  }
};

struct Multiplying : public ExpressionOperator {
  using ExpressionOperator::ExpressionOperator;

  double calculate(std::map<std::string, double> const& context) override {
    return _expr1->calculate(context) * _expr2->calculate(context);
  }

  std::string to_string(
      std::map<std::string, double> const* context = nullptr) override {
    return "(" + _expr1->to_string(context) + ")*(" +
           _expr2->to_string(context) + ")";
  }
};

class ExpressionFactory {
 public:
  ExpressionFactory() {
    for (int i = -5; i <= 256; ++i) {
      constants_[i] = std::make_shared<Constant>(i);
    }
  }

  std::shared_ptr<Constant> createConstant(double value) {
    if ((value == std::floor(value)) && (value >= -5) && (value <= 256)) {
      return constants_.at(static_cast<int>(value));
    }

    auto it = custom_constants_.find(value);
    if (it != custom_constants_.end()) {
      if (auto sp = it->second.lock()) {
        return sp;
      }
      custom_constants_.erase(it);
    }

    auto sp = std::make_shared<Constant>(value);
    custom_constants_[value] = sp;
    return sp;
  }

  std::shared_ptr<Variable> createVariable(std::string name) {
    auto it = variables_.find(name);
    if (it != variables_.end()) {
      if (auto sp = it->second.lock()) {
        return sp;
      }
      variables_.erase(it);
    }

    auto sp = std::make_shared<Variable>(name);
    variables_[name] = sp;
    return sp;
  }

  void feed_trash() {
    auto it = variables_.begin();
    while (it != variables_.end()) {
      if (it->second.expired()) {
        it = variables_.erase(it);
      }
      ++it;
    }
    auto it2 = custom_constants_.begin();
    while (it2 != custom_constants_.end()) {
      if (it2->second.expired()) {
        it2 = custom_constants_.erase(it2);
      }
      ++it2;
    }
  }

 private:
  std::unordered_map<int, std::shared_ptr<Constant>> constants_;
  std::unordered_map<double, std::weak_ptr<Constant>> custom_constants_;
  std::unordered_map<std::string, std::weak_ptr<Variable>> variables_;
};