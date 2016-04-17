#ifndef __PYLINGUAL_HPP__
#define __PYLINGUAL_HPP__
#include<vector>
#include<iostream>
#include<algorithm>
#include<iterator>
#include<string>
#include<map>

#include <boost/python.hpp>
#include <Python.h>
#include <converters.hpp>
#include <error_handle.hpp>

using namespace std;

class pylingual {

public:
  pylingual();
  ~pylingual() { ; }

  template<typename T>
  void Register(const char* varname, T&& var) {
    main_module.attr(varname) = var;
  }

  template<typename... Args>
  void function(const char* pyname, Args&&... args) {
    if (functions.count(pyname)>0) {
      functions[pyname](std::forward<Args>(args)...);
    }
  }

  template<typename T>
  boost::python::object VecToList(vector<T> _vec){
    Vector_to_python_list<T> Converter;
    auto List = Converter.convert(_vec);
    boost::python::object ListObj(handle<>(boost::python::borrowed(List)));
    return ListObj;
  }

  template<typename T>
  vector<T> ListToVec(boost::python::object _list){
    vector<T> Vec;
    for (int i=0;i<len(_list);i++) {
      Vec.push_back(extract<T>(_list[i]));
    }
    return Vec;
  }

  template<typename T>
  void call(const char* code_to_execute,char* var_to_extract,vector<T> &output) {
    exec(code_to_execute,main_namespace);
    auto buffer = main_module.attr(var_to_extract);
    output = ListToVec<T>(buffer);
  }

  void call(const char* code_to_execute) {
    exec(code_to_execute,main_namespace);
  }

  void import(const char* module, const char* function) {
    if (modules.count(module)>0){
      auto imported_function = modules[module].attr(function);
      functions[function] = imported_function;
    }else {
      auto python_module = boost::python::import(module);
      auto imported_function = python_module.attr(function);
      modules[module] = python_module;
      functions[function] = imported_function;
    }
  }

private:
  boost::python::object module;
  boost::python::object main_module;
  boost::python::object main_namespace;
  boost::python::object built_in;
  map<const char*,boost::python::object> modules;
  map<const char*,boost::python::object> functions;

};

pylingual::pylingual() {
  PyImport_AppendInittab("std", &initstd);
  Py_Initialize();
  // See PyImport_AppendInittab // BOOST_PYTHON_MODULE
  module = boost::python::import("std");
  modules["std"]=module;
  main_module = boost::python::import("__main__");
  modules["__main__"]=main_module;
  main_namespace = main_module.attr("__dict__");
  built_in = boost::python::import("__builtin__");
  modules["__builtin__"]=built_in;
}

#endif

