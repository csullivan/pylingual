#include <pylab.hpp>
//#include <error_handle.hpp>

pylab::pylab(){
  PyImport_AppendInittab("std", &initstd);
  Py_Initialize();
  module = import("std"); // See PyImport_AppendInittab // BOOST_PYTHON_MODULE
  modules["std"]=module;
  main_module = import("__main__");
  modules["__main__"]=main_module;
  main_namespace = main_module.attr("__dict__");
  built_in = import("__builtin__");
  modules["__builtin__"]=built_in;
  python_import("pylab","plot");
  python_import("pylab","savefig");  
  //  pylab_module = import("pylab");
  //  pylab_plot = pylab_module.attr("plot");
  //  pylab_save = pylab_module.attr("savefig");
  //  modules["pylab"]=pylab_module;
}
pylab::~pylab(){
}

void pylab::savefig(string filename){
  vector<string> file_name;
  file_name.push_back(filename);
  PyObject* pyString = StringConverter.convert(file_name);
  pyList listObj(handle<>(boost::python::borrowed(pyString)));
  //pylab_save(py::object(listObj[0]));
  this->functions["savefig"](py::object(listObj[0]));
}

void pylab::python_import(const char* module, const char* function){
  if (modules.count(module)>0){
    pyModule imported_function = modules[module].attr(function);
    functions[function] = imported_function;
  }else {
    pyModule python_module = import(module);
    pyFunc imported_function = python_module.attr(function);
    modules[module] = python_module;
    functions[function] = imported_function;
  }
}

void pylab::__py(const char* code_to_execute) {
  exec(code_to_execute,main_namespace);  
}


// py::object pylab::list(vector<double> _vec){
//   PyObject* List = DoubleConverter.convert(_vec);
//   pyList ListObj(handle<>(boost::python::borrowed(List)));
//   return ListObj;
// }

// vector<double> pylab::vec(pyList _list){
//   vector<double> Vec;
//   Vec = extract<vector<double> >(_list);
//   return Vec;
// }

   
  // try{
  // }catch(boost::python::error_already_set const &){
  // Parse and output the exception
  //  string perror_str = parse_python_exception();
  //  cout << "Error in Python: " << perror_str << endl;
  // }
