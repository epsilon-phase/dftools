#include "geometry.h"
Shape::Shape(){
}
Shape::~Shape(){}
void Shape::intersectionPoint(const Shape& i,int &n,std::vector<Point> &output)const{
    std::vector<Point> p1=i.getPoints();
    std::vector<Point> p2=getPoints();
    for(auto c:p1){
        for(auto d:p2){
            if(compareWithError(Distance(c,d),0,0.001)){
                //average together the error
                output.push_back(Point((c.x+d.x)/2,(c.y+d.y)/2));
            }
        }
    }
}
bool Shape::intersects(const Shape& i)const{
    std::vector<Point> p1,p2;
    p1=i.getPoints();
    p2=getPoints();
    for(auto c:p1){
        for(auto d:p2){
            if(compareWithError(Distance(c,d),0,0.001)){
                return true;
            }
        }
    }
    return false;
}
