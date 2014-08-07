#include<vector>
#include<iostream>
#include<algorithm>
#include<iterator>
#include<string>
#include <pylab.hpp>
#include <error_handle.hpp>

int main(){

  try{
  

    pylab plt;
    vector<double> x;
    vector<double> y;
    x.push_back(1);
    x.push_back(2);
    x.push_back(3);
    y.push_back(1);
    y.push_back(4);
    y.push_back(9);
    //plt.plot(x,y);
    //plt.savefig("/user/sullivan/public_html/pylab_class.pdf");

    plt.python_import("numpy","arange");    


    
    plt.python_import("numpy","diff");
    plt.python_import("numpy","arange");
    plt.python_import("__builtin__","list");    
    pyList myObj = plt.functions["diff"](plt.VecToList(x));

    plt.main_module.attr("myObj") = myObj; plt.__py("print myObj");
    plt.__py("import numpy as np");
    plt.__py("for el in range(0,10):\n"
	     "    print el;"
	     "    print el;");


    return 0;
    vector<float> rand;
    plt.__py("x = [float(x) for x in np.random.rand(10)]","x",rand);    
    for(int i=0;i<rand.size();i++){
      cout << rand[i] << endl;
    }

    //plt.__py("");
    return 0;

    //pyList mylist = plt.functions["list"](nparray);
    //pyList myObj = plt.functions["arange"](0,10,1);
    myObj = list(myObj);    
    float ghst;
    vector<float> myvec = plt.ListToVec(myObj,ghst);
    for(int i=0;i<myvec.size();i++){
      cout << myvec[i] << endl;
    }





    //pyList mylist = plt.functions["arange"](0,10,1);    
    //pyList mylist = plt.functions["diff"](plt.VecToList(x));


  }catch(boost::python::error_already_set const &){
    //Parse and output the exception
      string perror_str = parse_python_exception();
    cout << "Error in Python: " << perror_str << endl;
  }
}
