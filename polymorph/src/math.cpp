#include "math.hpp"

namespace math {

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
