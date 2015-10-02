#include "csv.h"
#include <iostream>
#include <cmath>
#include <list>
#include <iterator>
using namespace std;
struct cursor{
    float angle;
    float x=0,y=0;
    void left(float a){
        angle-=a;
        angle=fmod(angle,360.0);
    }
    void right(float a){
        angle+=a;
        angle=fmod(angle,360.0);
    }
    cursor forward(int d)const{
        cursor c;
        c.y=y+d*sin(angle*(3.1415/180.0));
        c.x=x+d*cos(angle*(3.1415/180.0));
        c.angle=angle;
        return c;
    }      
};
void half_sierpinski(list<cursor> &sheet,int size,int level){
    cursor i=sheet.front();
    if(level==0){
        sheet.push_front(i.forward(size));
        return;
    }
    half_sierpinski(sheet,size,level-1);
    i=sheet.front();
    i.left(45);
    sheet.push_front(i.forward(size*sqrt(2)));
    sheet.front().left(45);
    half_sierpinski(sheet,size,level-1);
    //in place modification of the first item on the queue.
    sheet.front().right(90);
    sheet.push_front(sheet.front().forward(size));
    sheet.front().right(90);
    half_sierpinski(sheet,size,level-1);
    sheet.front().left(45);
    sheet.push_front(sheet.front().forward(size*sqrt(2)));
    sheet.front().left(45);
    half_sierpinski(sheet,size,level-1);
}

void sierpinsky(list<cursor>& sheet,int size,int level){
    half_sierpinski(sheet,size,level);
    sheet.front().right(90);
    sheet.push_back(sheet.front().forward(size));
    sheet.front().right(90);
    half_sierpinski(sheet,size,level);
    sheet.front().right(90);
    sheet.push_back(sheet.front().forward(size));
    sheet.front().right(90);
}
void draw_turtle_like(csv& input,int size,int levels){
    list<cursor> c;
    cursor initial;
    initial.x=0;
    initial.y=0;
    initial.angle=90;
    c.push_front(initial);
    sierpinsky(c,size,levels);
    cerr<<"Sierpinsky is of size:"<<c.size()<<endl;
    int counter=0;
    cursor q;
    q=c.back();
    c.pop_back();
    while(!c.empty()){
        cursor n=c.back();
        c.pop_back();
        input.linefrom(floor(q.x),floor(q.y),
                floor(n.x),floor(n.y),
                "d",2);
        q=n;
    }
}
int main(int argc, char **argv){
    csv f;
    int size=2;
    int levels=3;
    if (argc>2){
      size=std::atoi(argv[1]);
      if(argc>3)
	levels=std::atoi(argv[2]);
    }
    draw_turtle_like(f,size,levels);
    cout<<f.getContents();
}
