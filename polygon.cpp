#include "geometry.h"
#include <climits>
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
double Polygon::getArea()const{
    double area=0;
    for(int i=0;i<points.size()-1;i++){
        area+=points[i].x*points[i+1].y-points[i+1].x*points[i].y;
    }
    return area/2;
}
#define MAX_POLY_CORNERS 100
std::vector<Point> Polygon::getInterior()const{
    std::vector<Point> result;
    int minY=INT_MAX,maxY=INT_MIN;
    int minX=INT_MAX,maxX=INT_MIN;
    for(auto i:points){
        if(i.x>maxX){
            maxX=std::floor(i.x);
        }else if(i.x<minX){
            minX=std::floor(i.x);
        }
        if(i.y>maxY){
            maxY=std::floor(i.y);
        }else if(i.y<minY){
            minY=std::floor(i.y);
        }
    }
    int nodes,nodeX[MAX_POLY_CORNERS],pixelX,pixelY,i,j,swap;
    for(pixelY=maxY;pixelY>minY;pixelY--){
        nodes=0;
        j=points.size()-1;
        for(i=0;i<points.size();i++){
            double polyY=points[i].y;
            double polyX=points[i].x;
            if(polyY<double(pixelY)&&points[j].y>=double(pixelY)
                    || points[j].y<double(pixelY)&&polyY>=double(pixelY)){
                nodeX[nodes++]=std::floor(polyX+(pixelY-polyY)
                        /(points[j].y-polyY)*(points[j].x-polyX));
            }
            j=i;
        }
        i=0;
        while(i<nodes-1){
            if(nodeX[i]>nodeX[i+1]){
                swap=nodeX[i];
                nodeX[i]=nodeX[i+1];
                nodeX[i+1]=swap;
                if(i)
                    i--;
            }else{
                i++;
            }
        }
        for(i=0;i<nodes;i+=1){
            if(nodeX[i]>=maxX)break;
            if(nodeX[i+1]>minX){
                if(nodeX[i]<nodeX[i])nodeX[i]=minX;
                if(nodeX[i+1]>maxX)nodeX[i+1]=maxX;
                for(j=nodeX[i];j<nodeX[i+1];j++)
                    result.push_back(Point(j,pixelY));
            }
        }
    }
    return result;
}

Polygon Polygon::Difference(const Polygon& a)const{
    ClipperLib::Paths thisone(1),thatone(1),solution;
    for(auto i:this->points){
        thisone[0]<<i.getAsClipper();
    }
    for(auto i:a.points)
        thatone[1]<<i.getAsClipper();
    ClipperLib::Clipper b;
    b.AddPaths(thisone,ClipperLib::PolyType::ptSubject,true);
    b.AddPaths(thatone,ClipperLib::PolyType::ptSubject,true);
    b.Execute(ClipperLib::ClipType::ctDifference,solution);
    Polygon r;
    for(auto c:solution[0]){
        r.addPoint(Point(c.X,c.Y));
    }
    return r;
}
Polygon Polygon::Union(const Polygon& a)const{
    ClipperLib::Paths thisone(1),thatone(1),solution;
    for(auto i:this->points){
        thisone[0]<<i.getAsClipper();
    }
    for(auto i:a.points)
        thatone[1]<<i.getAsClipper();
    ClipperLib::Clipper b;
    b.AddPaths(thisone,ClipperLib::PolyType::ptSubject,true);
    b.AddPaths(thatone,ClipperLib::PolyType::ptSubject,true);
    b.Execute(ClipperLib::ClipType::ctUnion,solution);
    Polygon r;
    for(auto c:solution[0]){
        r.addPoint(Point(c.X,c.Y));
    }
    return r;
}
Polygon Polygon::Intersection(const Polygon& a)const{
    ClipperLib::Paths thisone(1),thatone(1),solution;
    for(auto i:this->points){
        thisone[0]<<i.getAsClipper();
    }
    for(auto i:a.points)
        thatone[1]<<i.getAsClipper();
    ClipperLib::Clipper b;
    b.AddPaths(thisone,ClipperLib::PolyType::ptSubject,true);
    b.AddPaths(thatone,ClipperLib::PolyType::ptSubject,true);
    b.Execute(ClipperLib::ClipType::ctIntersection,solution);
    Polygon r;
    for(auto c:solution[0]){
        r.addPoint(Point(c.X,c.Y));
    }
    return r;
}
