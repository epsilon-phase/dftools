#ifndef TURTLE_HPP
#define TURTLE_HPP
#define PI 3.1415
#include <cmath>
struct cursor{
  float angle=0;
  float x=0,y=0;
  void left(float a){
    angle-=a;
    angle=std::fmod(angle,360.0);
  }
  void right(float a){
    angle+=a;
    angle=std::fmod(angle,360.0);
  }
  cursor forward(int d)const{
    using namespace std;
    cursor c;
    c.y=y+d*sin(angle*(PI/180.0));
    c.x=x+d*cos(angle*(PI/180.0));
    c.angle=angle;
    return c;
  }
};
#endif
