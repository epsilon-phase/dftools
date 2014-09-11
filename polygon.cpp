#include "geometry.h"

Polygon::Polygon(){}
Polygon::~Polygon(){}
void Polygon::addPoint(const Point &i){
    this->points.push_back(i);
}
std::vector<Point> Polygon::getPoints()const{
    Line v=Line(points[0],points[points.size()-1]);
    std::vector<Point> quip;
    for(Point c:v.getPoints())
        quip.push_back(c);
    for(int i=0;i<points.size()-1;i++){
        v=Line(points[i],points[i+1]);
        for(Point c:v.getPoints())
            quip.push_back(c);
    }
    return quip;
}
