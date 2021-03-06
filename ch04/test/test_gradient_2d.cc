#include "types.hpp"
#include "xtensor/xio.hpp"
#include "xt_helper.hpp"
#include <iostream>
#include <functional>

#include "matplotlibcpp.h"
namespace plt = matplotlibcpp;

template <typename T>
using func_t = std::function<T(T)>;

template <typename T>
T numerical_gradient_no_batch(func_t<T> f, T x)
{
  auto h = 1e-4;
  auto grad = x;

  for (uint idx=0; idx<x.size(); ++idx) {
    auto tmp_val = x[idx];
    x[idx] = tmp_val + h;
    auto fxh1 = f(x)[0]; // f(x+h)
    x[idx] = tmp_val - h;
    auto fxh2 = f(x)[0]; // f(x-h)

    grad[idx] = (fxh1 - fxh2) / (2*h);
    x[idx] = tmp_val; // back

  }

  return grad;
}

template <typename T>
T numerical_gradient(func_t<T> f, T x)
{
  if (xt::ndim(x) == 1) {
    return numerical_gradient_no_batch<T>(f, x);
  } else {
    auto grad = x;
    for (uint idx=0; idx<x.shape()[0]; ++idx) {
      // attention: often mistakes x[idx] ...
      auto xx = xt::view(x, idx);
      xt::view(grad, idx) = numerical_gradient_no_batch<T>(f, xx);
    }
    return grad;
  }
}

template <typename T>
T function_2(T x)
{
  if (xt::ndim(x) == 1) {
    return xt::sum<T>(x*x);
  } else {
    return xt::sum<T>(x*x, {1}); // axis=1
  }
}

int main()
{
  array_t<double> x0 = xt::arange(-2.0, 2.5, 0.25);
  array_t<double> x1 = xt::arange(-2.0, 2.5, 0.25);
  auto mz = xt::meshgrid(x0, x1);
  auto my = std::get<0>(mz);
  auto mx = std::get<1>(mz);
  auto fx = xt::flatten<array_t<double>>(mx);
  auto fy = xt::flatten<array_t<double>>(my);

  //auto gx = numerical_gradient<array_t<double>>(function_2<array_t<double>>, fx);
  //auto gy = numerical_gradient<array_t<double>>(function_2<array_t<double>>, fy);
  array_t<double> fz = xt::stack(xt::xtuple(fx, fy), 0);
  auto grad = numerical_gradient<array_t<double>>(function_2<array_t<double>>, fz);
  std::cout << grad << std::endl;

  plt::figure();
  //plt::quiver(fx, fy, -gx, -gy, "xy", "#666666");
  plt::xlim(-2, 2);
  plt::ylim(-2, 2);
  plt::xlabel("x0");
  plt::ylabel("x1");
  plt::grid(true);
  //plt::lagend();
  //plt::draw()
  //plt::show();

  return 0;
}
