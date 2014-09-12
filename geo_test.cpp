#include "geometry.h"
#include <iostream>
#include <cstdlib>
int main(){
    Circle q;
    q.radius=12;
    Circle b,quip;
    b.radius=12;
    b.thing=Point(13,0);
    quip.radius=8;
    quip.thing=Point(5,5);
    Line a;
    a=Line(Point(0,0),Point(0,14));
    int n;
    std::vector<Point> i;
    std::cout<<"Should be one\n";
    std::cout<<q.intersects(a)<<std::endl;
    q.intersectionPoint(a,n,i);
    std::cout<<"("<<i[0].x<<","<<i[0].y<<")\n";
    i.clear();
    q.intersectionPoint(b,n,i);
    q.intersectionPoint(quip,n,i);
    quip.intersectionPoint(b,n,i);
    std::cout<<"Printing "<<n<<"Points\n";
    for(int z=0;z<n;z++)
        std::cout<<"("<<i[z].x<<","<<i[z].y<<")\n";
    a.second=Point(2,2);
    std::cout<<"Should be zero\n";
    std::cout<<q.intersects(a)<<std::endl;
    return 0;
}
