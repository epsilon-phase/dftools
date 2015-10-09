#ifndef SVG_HPP
#define SVG_HPP
#include <map>
#include <vector>
#include <string>
#include <set>
class element;
class path;
class element{
public:
  element(const std::string&);
  ~element();
  void set_attribute(const std::string&, const std::string&);
  virtual std::string get_attribute(const std::string&)const;
  std::string get_name()const;
  virtual std::string serialize()const;
  bool removeAttribute(const std::string& s);
  std::vector<element*> getElementsByType(const std::string&)const;
  friend class svg;
protected:
  std::string name;
  mutable std::map<std::string,std::string> attributes;
  std::set<std::string> attrnames;
  std::vector<element*> contents;
};
class path:public element{
public:
  path();
  ~path();
 
  void r_lineTo(double x,double y);
  void r_moveTo(double x,double y);
  void r_quadTo(double x1,double y1,double x2,double y2);
  void r_ellipseTo(double rx,double ry,double xrot,double large_arc,double sweep,double x,double y);
  void r_cubicTo(double x1,double y1, double x2,double y2, double x,double y);
  void moveTo(double x,double y);
  void quadTo(double x1,double y1,double x2,double y2);
  void lineTo(double x,double y);
  void ellipseTo(double rx,double ry,double xrot,double large_arc,double sweep,double x,double y);
  void cubicTo(double x1,double y1,double x2,double y2,double x,double y);
  void close();
  virtual std::string get_attribute(const std::string&)const;
private:
  void recalc_path()const;
  void addC(int c,bool starting){}
  template<typename T, typename...Args>void  addC(int c,bool starting, T value, Args... e){
    if(starting){
      commands.push_back(c);
    }
    arguments.push_back(value);
    addC(c,false,e...);
    path_needs_update=true;
  }
  mutable bool path_needs_update=false;
  double position[2];
  std::vector<int> commands;
  std::vector<double> arguments;
};
/**
 * A placeholder for plain text encapsulated in an xml-style element. 
 */
class text:public element{
public:
  text();
  ~text();
  void setText(const std::string&);
  std::string getText()const;
  std::string serialize()const;
private:
  std::string txt;
};
class svg:public element{
public:
  svg();
  ~svg();
  void setsize(int w,int h,const std::string& units);
  path *beginPath();
  void endPath();
  element* startLinearGradient(const std::string& name);
  element* insert_stop(double offset,int r,int g,int b, double a=1.0);
  void insert_element_reference(element*,const std::string&,element* r);
private:
  element *defs=NULL;
  std::string width="10cm",
    height="8cm";
  std::string xmlns="http://www.w3.org/2000/svg",
    version="1.1";
  path *current=NULL;
  element *currentGradient=NULL;
};
enum path_commands{
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

#endif
