#include "svg.hpp"
#include <sstream>
#include <cstdio>
#include <algorithm>
#include <functional>
using namespace std;
svg::svg():element("svg"){
  set_attribute("xmlns",xmlns);
  set_attribute("version",version);
  set_attribute("width",width);
  set_attribute("height",height);
  
}
svg::~svg(){}
void svg::setsize(int w,int h,const string& unit){
  stringstream a,b;
  a<<w<<unit;
  b<<h<<unit;
  set_attribute("width",a.str());
  set_attribute("height",b.str());
}
path* svg::beginPath(){
  if(current==NULL){
    path * e=new path();
    contents.push_back(e);
    current=e;
    return e;
  }else return current;
}
void svg::endPath(){
  current=NULL;
}
element *svg::startLinearGradient(const std::string& name){
  element *f=new element("linearGradient");
  f->set_attribute("x1","0%");
  f->set_attribute("y1","0%");
  f->set_attribute("x2","100%");
  f->set_attribute("y2","100%");
  f->set_attribute("id",name);
  if(!defs){
    defs=new element("defs");
    contents.push_back(defs);
  }
  defs->contents.push_back(f);
  this->currentGradient=f;
  return f;
}
element* svg::insert_stop(double offset,int r,int g,int b,double a){
  if(currentGradient){
    element* stop=new element("stop");
    
    stop->set_attribute("offset",to_string(offset)+"%");
    stringstream f;
    f<<"stop-color:rgb("<<r<<","<<g<<","<<b<<");";
    f<<"stop-opacity:"<<a<<";";
    stop->set_attribute("style",f.str());
    currentGradient->contents.push_back(stop);
    return stop;
  }
  return NULL;
}
void svg::insert_element_reference(element * dest,const string& attr,element* other) {
  if(!dest||!other)
    return;
  dest->set_attribute(attr,"url(#"+other->get_attribute("id")+")");
}
/*string svg::serialize()const{
  stringstream f;
  f<<"<?xml version=\"1.0\" standalone=\"no\"?>"
    "<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\" "
  "\"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">"<<endl;
  
  f<<"<svg "<<"width=\""<<width <<"\" height=\""
   <<height<<"\" "<<"xmlns=\""<<xmlns<<"\" version=\""
   <<version<<"\">"<<endl;
  for(auto element : body){
    f<<element->serialize()<<endl;
  }
  f<<"</svg>";
  return f.str();
  }*/
element::element(const string& n):
  name(n){
}
element::~element(){
  for(auto i:contents)
    delete i;
}
string element::get_name()const{
  return name;
}
bool element::removeAttribute(const std::string& s){
  this->attributes.erase(s);
  return  this->attrnames.erase(s);
}
string element::get_attribute(const string& attr)const{
  return attributes.find(attr)->second;
}
void element::set_attribute(const string& atn, const string& atv){
  attributes[atn]=atv;
  attrnames.insert(atn);
}
vector<element*> element::getElementsByType(const string& type)const{
  vector<element*> results;
  for(auto i : contents){
    if(!i->contents.empty()){
      auto tmp=i->getElementsByType(type);
      results.insert(results.end(), tmp.begin(),tmp.end());
    }
    if(i->name == type)
      results.push_back(i);
  }
  return results;
}
string element::serialize()const{
  stringstream e;
  e<<"<"<<name<<" ";
  for(auto i : attrnames){
    e<<i<<"=\"";
    e<<get_attribute(i)<<"\" ";
  }
  if(contents.empty()){
    e<<"/>";
  }else{
    e<<">"<<endl;
    for(auto i:contents){
      e<<i->serialize();
      e<<"\n";
    }
    e<<"</"<<name<<">";
  }
  return e.str();
}
text::text():element(""){}
text::~text(){}
void text::setText(const string& t){
  stringstream f;
  for(auto i : t)
    {
      if ( i == '&')
	f<<"&amp;";
      else
	f<<i;
    }
  txt=f.str();
}
string text::getText()const{
  return txt;
}
string text::serialize()const{
  return txt;
}
path::path():element("path"){
  set_attribute("stroke","black");
  set_attribute("d","");
  set_attribute("fill","none");
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
  if(name=="d"&&path_needs_update){
    recalc_path();
  }
  return attributes.find(name)->second;
}
path::~path(){}
void path::recalc_path()const{
  stringstream e;
  int argdex=0;
  int prevarg=-1;
  int arg_consumption=0;
  for(auto i : commands){
    if(prevarg!=i){
      prevarg=i;
      arg_consumption=arg_consp[i];
      
    }
    e<<cname[i];
    for(int i=0;i<arg_consumption;++i,++argdex){
      e<<arguments[argdex]<<" ";
    }
  }
  this->path_needs_update=false;
  attributes["d"]=e.str();
}
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
