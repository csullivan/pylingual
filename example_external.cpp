#include <vector>
#include <iostream>
#include <string>
#include <pylingual.hpp>

int main(){

  try{

    pylingual py;

    py.call("x = 42");
    auto x = py.get<double>("x");
    cout << x << endl;

    return 0;


  }catch(boost::python::error_already_set const &){
    //Parse and output the exception
      string perror_str = parse_python_exception();
    cout << "Error in Python: " << perror_str << endl;
  }
}
