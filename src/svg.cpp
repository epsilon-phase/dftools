#include "svg.hpp"
#include <sstream>
using namespace std;
enum{
  rline=0,
  rquad,
  rcubic,
  rellipse,
  rmove,
  moveto,
  lineto,
  quadto,
  ellipseto,
  cubicto,
  path_close
};
element::element(const string& n):
  name(n){
}
element::~element(){
}
string element::get_name()const{
  return name;
}
string element::get_attribute(const string& attr)const{
  return attributes.find(attr)->second;
}
void element::set_attribute(const string& atn, const string& atv){
  attributes[atn]=atv;
}
path::path():element("path"){
  attributes["d"]="";
}
std::map<int,int> arg_consp={
  {rline,2},
  {lineto,2},
  {rmove,2},
  {moveto,2},
  {rquad,4},
  {quadto,4},
  {ellipseto,8},
  {rellipse,8},
  {rcubic,6},
  {cubicto,6},
  {path_close,0}
};
std::map<int,string> cname={
  {rline,"l"},
  {lineto,"L"},
  {rmove,"m"},
  {moveto,"M"},
  {rquad,"q"},
  {quadto,"Q"},
  {ellipseto,"A"},
  {rellipse,"a"},
  {rcubic,"c"},
  {cubicto,"C"},
  {path_close,"Z"}
};
std::string path::get_attribute(const string& name)const{
  if(name=="d"){
    stringstream e;
    int argdex=0;
    int prevarg=-1;
    int arg_consumption=0;
    for(auto i : commands){
      if(prevarg!=i){
	arg_consumption=arg_consp[i];
	e<<cname[i];
      }
      for(int i=0;i<arg_consumption;++i,++argdex){
	e<<arguments[argdex]<<" ";
      }
    }
  }else
    return attributes.find(name)->second;
}
path::~path(){}

void path::r_lineTo(double x,double y){
  position[0]+=x;
  position[1]+=y;
  addC(rline,true,x,y);
}
void path::r_ellipseTo(double rx,double ry,double xrot, double large_arg, double sweep,double x,double y){
  addC(rellipse,true,rx,ry,xrot,large_arg,sweep,x,y);
  position[0]+=x;
  position[1]+=y;
}
void path::r_moveTo(double x,double y){
  addC(rmove,true,x,y);
  position[0]+=x;
  position[1]+=y;
}
void path::r_cubicTo(double x1,double y1,double x2,double y2, double x,double y){
  position[0]+=x;
  position[1]+=y;
  addC(rcubic,true,x1,y1,x2,y2,x,y);
}
void path::r_quadTo(double x1,double y1,double x,double y){
  position[0]+=x;
  position[1]+=y;
  addC(rquad,x1,y1,x,y);
}
void path::lineTo(double x,double y){
  position[0]=x;
  position[1]=y;
  addC(lineto,true,x,y);
}
void path::moveTo(double x,double y){
  position[0]=x;
  position[1]=y;
  addC(moveto,true,x,y);
}
void path::ellipseTo(double rx,double ry,double xrot,double large_arc,double sweep,double x,double y){
  position[0]=x;
  position[1]=y;
  addC(ellipseto,true,rx,ry,xrot,large_arc,sweep,x,y);
}
void path::cubicTo(double x1,double y1,double x2,double y2, double x,double y){
  position[0]=x;
  position[1]=y;
  addC(cubicto,true,x1,y1,x2,y2,x,y);
}
void path::close(){
  commands.push_back(path_close);
}
