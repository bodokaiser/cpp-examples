#include "math.hpp"

namespace math {

double AddPolicy::operate(double a, double b) const {
  return a + b;
}

double SubPolicy::operate(double a, double b) const {
  return a - b;
}

double MulPolicy::operate(double a, double b) const {
  return a * b;
}

double DivPolicy::operate(double a, double b) const {
  return a / b;
}

template <typename OperatePolicy>
Operation<OperatePolicy>::Operation(std::shared_ptr<Expression> lvalue,
                                    std::shared_ptr<Expression> rvalue)
    : lvalue_(std::move(lvalue)), rvalue_(std::move(rvalue)) {}

template <typename OperatePolicy>
std::string Operation<OperatePolicy>::str() const {
  std::stringstream stream;
  stream << lvalue_->str() << " " << OperatePolicy::symbol << " "
         << rvalue_->str();

  return stream.str();
}

template class Operation<AddPolicy>;
template class Operation<SubPolicy>;
template class Operation<MulPolicy>;
template class Operation<DivPolicy>;

std::string Constant::str() const {
  std::stringstream stream;
  stream << value_;

  return stream.str();
}

std::string Variable::str() const {
  std::stringstream stream;
  stream << name_;

  return stream.str();
}

}  // namespace math
