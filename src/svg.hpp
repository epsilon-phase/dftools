#ifndef SVG_HPP
#define SVG_HPP
#include <map>
#include <vector>
#include <string>
class element;
class path;
class svg{
private:
  std::string width,
    height;
};
class element{
public:
  element(const std::string&);
  ~element();
  void set_attribute(const std::string&, const std::string&);
  virtual std::string get_attribute(const std::string&)const;
  std::string get_name()const;
protected:
  std::string name;
  std::map<std::string,std::string> attributes;
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
  void addC(int c,bool starting){}
  template<typename T, typename...Args>void  addC(int c,bool starting, T value, Args... e){
    if(starting){
      commands.push_back(c);
    }
    arguments.push_back(value);
    addC(c,false,e...);
  }
  double position[2];
  std::vector<int> commands;
  std::vector<double> arguments;
};
#endif
