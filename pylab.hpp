#ifndef __PYLAB_HPP
#define __PYLAB_HPP
#include<vector>
#include<iostream>
#include<algorithm>
#include<iterator>
#include<string>
#include<map>

#include <boost/python.hpp>
#include <Python.h>
#include <pylab_converters.hpp>

namespace py = boost::python;
using namespace std;


typedef py::object pyModule;
typedef py::object pyFunc;
typedef py::object pyList;


class pylab{

public:
  pylab();
  ~pylab();  
  pyModule module;
  pyModule main_module;
  pyFunc   main_namespace;
  pyModule built_in;
  //pyModule pylab_module;
  //pyFunc   pylab_plot;
  //pyFunc   pylab_save;
  map<const char*,pyModule> modules;
  map<const char*,pyFunc> functions;


  template<typename T>
  void plot(vector<T> x, vector<T> y){
    Vector_to_python_list<T> Converter;
    PyObject* xList = Converter.convert(x);
    PyObject* yList = Converter.convert(y);
    pyList xObj(handle<>(boost::python::borrowed(xList)));
    pyList yObj(handle<>(boost::python::borrowed(yList)));
    this->functions["plot"](xObj,yObj);
  }
  template<typename T>
  pyList VecToList(vector<T> _vec){
    Vector_to_python_list<T> Converter;
    PyObject* List = Converter.convert(_vec);
    pyList ListObj(handle<>(boost::python::borrowed(List)));
    return ListObj;
  }

  template<typename T>
  vector<T> ListToVec(pyList _list, T){
    vector<T> Vec;
    for (int i=0;i<len(_list);i++) {
      Vec.push_back(extract<T>(_list[i]));
    }
    return Vec;
  }

  void __py(const char* code_to_execute);

  template<typename T>
  void __py(const char* code_to_execute,char* var_to_extract,vector<T> &output) {
    exec(code_to_execute,main_namespace);  
    pyList buffer = main_module.attr(var_to_extract);
    T basetype;
    output = ListToVec(buffer,basetype);    
  }


  void savefig(string filename);  
  void python_import(const char* module, const char* function);


  //pyList list(vector<double> _vec);
  //  vector<double> vec(pyList _list);

  Vector_to_python_list<double> DoubleConverter;
  Vector_to_python_list<string> StringConverter;
};

#endif

