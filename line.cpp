#include "geometry.h"
using namespace std;
bool Line::doBoundingBoxesIntersect(const Line &b)const
{
    return first.x<=b.second.x
        || second.x>=b.first.x
        || first.y<=b.second.y
        || second.y>=b.first.y;
}
double Line::length()const{
    return sqrt((first.x-second.x)*(first.x*second.x)+(first.y-second.y)*(first.y-second.y));
}
bool Line::isPointOnLine(Point a)const
{
    Line atmp=Line(Point(0.0,0.0),Point(second.x-first.x, second.y-first.y));
    Point btmp=Point(a.x-first.x,a.y-first.y);
    double r=atmp.second.crossProduct(btmp);
    return std::abs(r)<EPSILON;
}
bool Line::isPointRightOfLine(Point b)const{
    Line atmp(Point(0,0),
            Point(second.x-first.x,second.y-first.y));
    Point btmp(b.x-first.x,b.y-first.y);
    return atmp.second.crossProduct(btmp)<0;
}
bool Line::touchesOrCrossesLine(const Line &b)const{
    return isPointOnLine(b.first)
        || isPointOnLine(b.second)
        || (isPointRightOfLine(b.first)^ isPointRightOfLine(b.second));
}
bool Line::doLinesIntersect(const Line &b)const{
    return doBoundingBoxesIntersect(b)
        && touchesOrCrossesLine(b)
        && b.touchesOrCrossesLine(*this);
}
vector<Point> Line::getPoints()const{
    double length= sqrt((first.x-second.x)*(first.x*second.x)+(first.y-second.y)*(first.y-second.y));
    vector<Point> results;
    for(double i=0;i<1;i+=1/length){
        results.push_back(Point(i*first.x+(1-i)*second.x,i*first.y+(1-i)*second.y));
    }
return results;
}
