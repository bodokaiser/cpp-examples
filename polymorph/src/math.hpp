#pragma once

#include <ostream>
#include <sstream>

namespace math {

class Expression {
 public:
  virtual std::string str() const = 0;
};

struct AddPolicy {
  double operate(double a, double b) const;
  static const char symbol = '+';
};

struct SubPolicy {
  double operate(double a, double b) const;
  static const char symbol = '-';
};

struct MulPolicy {
  double operate(double a, double b) const;
  static const char symbol = '*';
};

struct DivPolicy {
  double operate(double a, double b) const;
  static const char symbol = '/';
};

template <typename OperatePolicy>
class Operation : public Expression, private OperatePolicy {
 public:
  Operation(std::shared_ptr<Expression> lvalue,
            std::shared_ptr<Expression> rvalue);

 private:
  std::shared_ptr<Expression> lvalue_;
  std::shared_ptr<Expression> rvalue_;
};

using Sum = Operation<AddPolicy>;
using Sub = Operation<SubPolicy>;
using Mul = Operation<MulPolicy>;
using Dev = Operation<DivPolicy>;

class Constant : public Expression {
 public:
  explicit Constant(double value) : value_(value) {}

  std::string str() const final;

 private:
  double value_;
};

class Variable : public Expression {
 public:
  explicit Variable(std::string name) : name_(std::move(name)) {}

  std::string str() const final;

 private:
  std::string name_;
};

}  // namespace math
