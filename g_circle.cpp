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
double Distance(Point x,Point y){
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
    double o=b.thing.y,k1=thing.y,h1=thing.x,l=b.thing.x,b=b.radius,
           r=radius;
    double x=0,y=0;
    if(o==k1&&h1-l!=0.0){
        x=b*b+h1*h1-l*l-r*r;
        x/=(2*h1-l);
        y=b*b+h1*h1-l*l-r*r;
        y*=y;
        y/=4*(h1-l)*(h1-l);
        y+=(l*((b*b+h1*h1-l*l-r*r)(b*b+h1*h1-l*l-r*r)))/(h1-l);
        y+=b*b-l*l;
        y=sqrt(y)*2;
        output.push_back(Point(x,(2*o-2*y)/2));
        output.push_back(Point(x,(2*o+2*y)/2));

    }else{
        if(h1*h1-2*h1*l+k1*k1-2*k1*o+o*o!=0&&k1-o!=0){
            /*
            double t1,t2,t3,t4,t5,y1,y2,y3;
            x=b*b*h1-b*b*l;
            t1=k1-o;
            t1*=t1;
            t2=b*b*b*b
                -2*b*b*h1*h1+
                4*b*b*h1*l-
                2*b*b*k1*k1+
                4*b*b*k1*o
                - 2*b*b*l*l
                -2*b*b*o*o
                -2*b*b*r*r
                +h1*h1*h1*h1
                -4*h1*h1*h1*l
                +2*h1*h1*r*r
                -4*h1*k1*k1*l
                +8*h1*k1*l*o
                -4*h1*l*l*l
                -4*h1*l*o*o
                +4*h1*l*r*r
                +k1*k1*k1*k1
                -4*k1*k1*k1*o
                +2*k1*k1*l*l
                +6*k1*k1*o*o
                -2*k1*k1*r*r
                -4*k1*l*l*o
                -4*k1*o*o*o+
                2*k1*k1*l*l
                +6*k1*k1*o*o
                -2*k*k*r*r
                -4*k1*l*l*o
                -4*k1*o*o*o+
                4*k1*o*r2
                +l*l*l*l
                +2*l*l*o*o-
                2*l*l*r*r
                +o*o*o*o
                -2*o*o*r*r
                +r*r*r*r;
            t3=h1*h1*h1-h1*h1*l+h1*k1*k1-2*h1*k1*o-h1*l*l+
                h1*o*o
                -h1*r*r
                +k1*k1*l-2*k1*l*o
                +l*l*l
                +l*o*o
                +l*r*r;
            t2=sqrt(t2*t1);
            t4=t2+t3+x;
            t5=x-t2+t3;
            y1=b*b*k1*k1-2*b*b*k1*o+b*b*o*o;
            y2=
            */
        }
    }
    for(double o=0;o<2*PI;o+=0.001){
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
