#include<vector>
#include<iostream>
#include<algorithm>
#include<iterator>
#include<string>
#include <pylab.hpp>
#include <error_handle.hpp>

int main(){

  try{
  

    pylab py;

    //py.python_import("numpy","diff");
    //py.python_import("__builtin__","list");    
    //pyList myObj = py.functions["diff"](py.VecToList(x));
    //py.main_module.attr("myObj") = myObj; py.__py("print myObj"); // bind python obj in cpp to python keyword

    py.python_import("pylab","plot");
    py.python_import("pylab","savefig");
    py.python_import("__builtin__","list");    
    
    vector<float> rand;
    py.__py("import numpy as np; import pylab");
    // create an arbitrary list in python and extract it out into c++ land
    py.__py("x = [float(x) for x in np.random.rand(10)]","x",rand);
    for(int i=0;i<rand.size();i++){
      cout << rand[i] << endl;
    }
    // send it back to python as a new list
    py.functions["plot"](py.VecToList(rand),py.VecToList(rand));
    py.__py("pylab.xlim(0.1,0.5)");
    // call savefig via c++ function
    py.functions["savefig"]("./test.pdf");
    // or via python
    py.__py("pylab.savefig('./test.pdf')");

    return 0;

    // myObj = list(myObj);    
    // float ghst;
    // vector<float> myvec = py.ListToVec(myObj,ghst);
    // for(int i=0;i<myvec.size();i++){
    //   cout << myvec[i] << endl;
    // }





    //pyList mylist = py.functions["arange"](0,10,1);    
    //pyList mylist = py.functions["diff"](py.VecToList(x));


  }catch(boost::python::error_already_set const &){
    //Parse and output the exception
      string perror_str = parse_python_exception();
    cout << "Error in Python: " << perror_str << endl;
  }
}
