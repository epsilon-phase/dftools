#ifndef GEOMETRY_H
#define GEOMETRY_H
#include <cmath>
#include <vector>
#define EPSILON 0.0001
// Point class, specifies a point on a *nearly* continuous range across two
// axis.

class Point{
    public:
        double x,y;
        Point():x(0.0),y(0.0)
    {}
        Point(double x,double y):
            x(x),y(y){}
        double crossProduct(const Point &a)const{
            return x*a.y-a.x*y;
        }
        double dot(const Point &a)const{
            return a.x*x+a.y*y;
        }
        void add(double dx,double dy){
            x+=dx;
            y+=dy;
        }
        Point getDifference(Point a)const{
            return Point(a.x-x,a.y-y);
        }
};
double Distance(const Point&a,const Point&b);
int compareWithError(double,double,double);
//class for generic shape access, you know, for shape things.
class Shape{
    public:
        Shape();
        ~Shape();
        virtual std::vector<Point> getPoints()const=0;
        virtual bool intersects(const Shape&)const;
        virtual void intersectionPoint(const Shape&,int&,std::vector<Point>&)const;
};
class Line:public Shape{
    public:
        Point first,second;
        Line(){}
        Line(const Point& a,const Point &b):first(a),second(b){
            
        }
        ~Line(){}
        bool doBoundingBoxesIntersect(const Line& b)const;
        bool isPointOnLine(Point a)const;
        bool isPointRightOfLine(Point b)const;
        bool touchesOrCrossesLine(const Line &b)const;
        bool doLinesIntersect(const Line& b)const;
        double length()const;
        std::vector<Point> getPoints()const;
};
class Circle:public Shape{
public:
    Point thing;
    double radius;
    Circle():radius(0),thing(){}
    Circle(Point center,double radius):thing(center),radius(radius)
    {}
    ~Circle(){}
    bool intersects(const Circle &b)const;
    bool intersects(const Line &b)const;
    void intersectionPoint(const Circle& b,int &n,std::vector<Point> &output)const;
    void intersectionPoint(const Line &b,int &n, std::vector<Point> &output)const;
    bool isOnCircle(const Point &i)const;
    bool isOnCircle(const Point &i,double error)const;
    std::vector<Point> getPoints()const;
};


class Polygon:public Shape{
    std::vector<Point> points;
    public:
    Polygon();
    ~Polygon();
    std::vector<Point> getPoints()const;
    void addPoint(const Point &i);
};
    
#endif
