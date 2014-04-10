#include <pylab.hpp>
#include <pylab_converters.hpp>
#include <error_handle.hpp>



pylab::pylab(){
  PyImport_AppendInittab( "std", &initstd);  // Necessary for vector/list conversions
  Py_Initialize();
  module = import("std"); // See PyImport_AppendInittab
  main_module = import("__main__");
  main_namespace = main_module.attr("__dict__");
  built_in = import("__builtin__");
  pylab_module = import("pylab");
  pylab_plot = pylab_module.attr("plot");
  pylab_save = pylab_module.attr("savefig");
}
pylab::~pylab(){
}
//template<typename T>
void pylab::plot(vector<double> x, vector<double> y){
  Vector_to_python_list<double> converter;
  PyObject* xList = converter.convert(x);
  PyObject* yList = converter.convert(y);
  py::object xObj(handle<>(boost::python::borrowed(xList)));
  py::object yObj(handle<>(boost::python::borrowed(yList)));
  pylab_plot(xObj,yObj);

}
void pylab::savefig(string filename){
  Vector_to_python_list<string> converter;
  vector<string> file_name;
  file_name.push_back(filename);
  PyObject* pyString = converter.convert(file_name);
  py::object listObj(handle<>(boost::python::borrowed(pyString)));
  pylab_save(py::object(listObj[0]));
}





   
  // try{
  // }catch(boost::python::error_already_set const &){
  // Parse and output the exception
  //  string perror_str = parse_python_exception();
  //  cout << "Error in Python: " << perror_str << endl;
  // }
