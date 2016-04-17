#include <vector>
#include <iostream>
#include <string>
#include <pylab.hpp>
#include <error_handle.hpp>

int main(){

  try{

    pylab py;

    py.import("pylab","plot");
    py.import("pylab","savefig");
    py.import("__builtin__","list");
    py.call("import numpy as np; import pylab");
    // create an arbitrary list in python and extract it out into c++ land
    vector<float> rand;
    py.call("x = [float(x) for x in np.random.rand(10)]","x",rand);
    // convert vector to list and register in python
    py.Register("mylist",py.VecToList(rand));
    py.call("print mylist");

    return 0;





  }catch(boost::python::error_already_set const &){
    //Parse and output the exception
      string perror_str = parse_python_exception();
    cout << "Error in Python: " << perror_str << endl;
  }
}
