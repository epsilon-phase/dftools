#include "geometry.h"
#include <cmath>
#include <vector>
#ifdef DEBUG
#include <iostream>
#define PRINT_DEBUG(x) cout<<x<<endl;
#else
#define PRINT_DEBUG(X)
#endif
#define PI 3.141592
using namespace std;
inline double square(double r){
    return r*r;
}
double Distance(const Point &x,const Point &y){
    return std::sqrt(square(x.x-y.x)+square(x.y-y.y));
}
bool Circle::intersects(const Circle &b)const{
    return Distance(thing,b.thing)<=radius+b.radius;
}

bool Circle::intersects(const Line &e)const{
    Point d,f;
    d=e.first.getDifference(e.second);
    f=thing.getDifference(e.first);
    double a=d.dot(d);
    double b=2*f.dot(d);
    double c=f.dot(f)-radius*radius;
    double discriminant=b*b-4*a*c;
    if(discriminant<0)
    {
        //nothing
    }else{
        discriminant=sqrt(discriminant);
        double t1=(-b-discriminant)/(2*a);
        double t2=(-b+discriminant)/(2*a);
        if(t1>=0&&t1<=1)
        {
            return true;
        }
        if(t2>=0&&t2<=1)
        {
            return true;
        }
    }
    return false;
}
double sgn(double x){
    return x<0?-1:1;
}
int compareWithError(double x,double y,double error=0.01){
    if(abs(x-y)<error){
        return 0;
    }else
        return x<y?-1:1;
}
int compareWithError(double a,double a2,double b,double error){
    double ac,ac2;
    ac=abs(a-b);
    ac2=abs(a2-b);
    if(ac<error&&ac2<error)
    {
        return ac<=ac2?2:3;
    }else
    {
        if(ac<error||ac2<error)
            return ac<error?1:(ac2<error?2:0);
        else
        {
            return ac<ac2?-1:-2;
        }
    }
}
    
void Circle::intersectionPoint(const Line& b,int &n, std::vector<Point> &output)const{
    for(double t=0;t<1;t+=0.001){
        Point i=(Point(t*b.first.x+(1-t)*b.second.x,t*b.first.y+(1-t)*b.second.y));
        if(isOnCircle(i)){
            output.push_back(i);
            PRINT_DEBUG("DEBUG ("<<i.x<<","<<i.y<<")");
        }
    }
    n=output.size();
}
void Circle::intersectionPoint(const Circle& b,int &n,std::vector<Point> &output)const{
    Point i;
    std::vector<Point> q;
    int isize=output.size();
    for(double o=0;o<2*PI*radius;o+=1.0/(2*PI*radius)){
        i.x=cos(o)*radius+thing.x;
        i.y=sin(o)*radius+thing.y;
        if(b.isOnCircle(i)){   
            output.push_back(i);
        }
    }
    n=output.size();
}

vector<Point> Circle::getPoints()const{
    vector<Point> result;
    double point_number=radius*2*3.1415;
    for(double i=0;i<2*PI;i+=1/point_number){
        result.push_back(Point(thing.x+radius*cos(i),thing.y+radius*sin(i)));
    }
    return result;
}
bool Circle::isOnCircle(const Point &u)const{
    return compareWithError(Distance(thing,u),radius,0.005)==0;
}
bool Circle::isOnCircle(const Point &a,double error)const{
    return compareWithError(Distance(thing,a),radius,error);
}
