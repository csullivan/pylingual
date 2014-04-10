#include<vector>
#include<iostream>
#include<algorithm>
#include<iterator>
#include<string>
#include <pylab.hpp>

int main(){
  pylab plt;
  vector<double> x;
  vector<double> y;
  x.push_back(1);
  x.push_back(2);
  x.push_back(3);
  y.push_back(1);
  y.push_back(4);
  y.push_back(9);
  plt.plot(x,y);
  plt.savefig("/user/sullivan/public_html/pylab_class.pdf");
}
