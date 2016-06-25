#include <boost/python.hpp>
#include <boost/numpy.hpp>
#include <stdio.h>

#include <stdexcept>
#include <algorithm>

namespace np = boost::numpy;

char const* yay(np::ndarray a)
{
  int nd = a.get_nd();
  if (nd != 1)
    throw std::runtime_error("a must be 1-dimensional");
  size_t N = a.shape(0);
  if (a.get_dtype() != np::dtype::get_builtin<double>())
    throw std::runtime_error("a must be float64 array");
  double *p = reinterpret_cast<double *>(a.get_data());
  p[0] = p[0]*2;
  return "Yay!";
}


BOOST_PYTHON_MODULE(libyay)
{
  using namespace boost::python;
  Py_Initialize();
  np::initialize(); // important
  def("yay", yay);
  
}