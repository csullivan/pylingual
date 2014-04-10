#ifndef __PYLAB_HPP
#define __PYLAB_HPP

#include<vector>
#include<iostream>
#include<algorithm>
#include<iterator>
#include<string>

#include <boost/python.hpp>
#include <Python.h>

namespace py = boost::python;
using namespace std;

class pylab{

public:
  pylab();
  ~pylab();  
  py::object module;
  py::object main_module;
  py::object main_namespace;
  py::object built_in;
  py::object pylab_module;
  py::object pylab_plot;
  py::object pylab_save;

  //  template<typename T>
  void plot(vector<double> x, vector<double> y);
  void savefig(string filename);


};

#endif

