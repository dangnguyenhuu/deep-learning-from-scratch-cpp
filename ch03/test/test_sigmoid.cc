#include "types.hpp"
#include "sigmoid.hpp"
#include "matplotlibcpp.h"
//#include "xtensor/xio.hpp"
//#include <iostream>

namespace plt = matplotlibcpp;

int main() {
  array_t<double> x = xt::arange<double>(-5.0, 5.0, 0.1);
  array_t<double> y = sigmoid(x);
  //std::cout << y << std::endl;

  auto vx = arr_to_vec(x);
  auto vy = arr_to_vec(y);
  plt::plot(vx, vy);
  plt::ylim(-0.1, 1.1);
  plt::show();

  return 0;
}
