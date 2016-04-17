#include <vector>
#include <iostream>
#include <string>
#include <pylingual.hpp>

int main(){

  try{

    pylingual py;

    py.import("pylab","plot");
    py.import("pylab","savefig");
    py.import("__builtin__","list");

    py.call("import numpy as np; import pylab");
    // create an arbitrary list in python and extract it out into c++ land
    vector<float> rand;
    py.call("x = [float(x) for x in np.random.rand(10)]","x",rand);
    // send it back to python as a new list
    auto xlist = py.VecToList(rand);
    //py.functions["plot"](xlist,xlist);
    py.function("plot",xlist,xlist);
    // call xlim directly in python
    py.call("pylab.xlim(0.1,0.5)");
    // call savefig via c++ function
    //py.functions["savefig"]("./from_cpp.pdf");
    py.function("savefig","./from_cpp.pdf");
    // or via python
    py.call("pylab.savefig('./from_py.pdf')");


    return 0;





  }catch(boost::python::error_already_set const &){
    //Parse and output the exception
      string perror_str = parse_python_exception();
    cout << "Error in Python: " << perror_str << endl;
  }
}
