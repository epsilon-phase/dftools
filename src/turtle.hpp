#ifndef TURTLE_HPP
#define TURTLE_HPP
#define PI 3.14159265358979323846
#include <cmath>
struct cursor{
  double angle=0;
  double x=0,y=0;
  void left(double a){
    angle-=a;
    angle=std::fmod(angle,360.0);
  }
  void right(double a){
    angle+=a;
    angle=std::fmod(angle,360.0);
  }
  cursor forward(double d)const{
    using namespace std;
    cursor c;
    c.y=y+d*sin(angle*(PI/180.0));
    c.x=x+d*cos(angle*(PI/180.0));
    c.angle=angle;
    return c;
  }
};
#undef PI
#endif
