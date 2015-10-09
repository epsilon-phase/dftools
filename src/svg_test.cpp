#include "svg.hpp"
#include <iostream>
#include <fstream>
using namespace std;

int main(){
  path e;
  e.moveTo(0,0);
  e.r_lineTo(20,0);
  e.r_moveTo(20,0);
  e.r_lineTo(20,0);
  cout<<e.serialize()<<endl;
}
