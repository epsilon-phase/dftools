#include <iostream>
#include <cstdlib>
#include <map>
#include <string>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <list>
#include <utility>
#include "csv.h"
using namespace std;
const float reduction=1.41421;
struct position{
    position(){
        x=0;y=0;
    }
    position(int x,int y){
        this->x=x;
        this->y=y;
    }
    int x,y;
};
class PComp{
    public:
bool operator()(const position& a,const position& b)const{
    return (a.x==b.x)?a.y<b.y:a.x<b.x;
}
};
bool operator==(const position&a,const position& b){
    return a.x==b.x&&a.y==b.y;
}
class grid{
    int maxX,maxY;
    int minX,minY;
    map<position,char,PComp> content;
    void setMaxX(int x){
        this->maxX=x;
        minX=-x;
    }
    void setMaxY(int y){
        this->maxY=y;
        minY=-y;
    }
    public:
    grid(){
        setMaxX(10);
        setMaxY(10);
    }
    ~grid(){}
    void addChar(const position& c,char d){
        if(c.x>maxX)
            maxX=c.x;
        if(c.y>maxY)
            maxY=c.y;
        if(c.x<minX)
            minX=c.x;
        if(c.y<minY)
            minY=c.y;
        content[c]=d;
    }
    char getChar(const position& p)const {
        if(content.find(p)!=content.end())
            return content.find(p)->second;
        //return a space instead
        return ' ';
    }
    position drawVLine(const position &start,int length,char draw,bool up=true){
        position i=start;
        for(int y=0;y<length;y++){
            addChar(i,draw);
            if(up){
                i.y++;
            }else
                i.y--;
        }
        return i;
    }
    position drawHLine(const position &start,int length,char draw,bool left=true){
        position i=start;
        for(int x=0;x<length;x++){
            addChar(i,draw);
            if(left)
                i.x++;
            else
                i.x--;
        }
        return i;
    }
    string ToString() const{
        int trposx=0,trposy=0;
        string accum;//=string("#dig");
       // for(int i=0;i<abs(minX)+maxX;i++){
       //     accum+=",";
       // }
       // accum+="\n";
        accum.resize(2*maxX*maxY);
        position center;
        for(int x=minX;x<=maxX;x++){
            for(int y=minY;y<=maxY;y++){
                trposx++;
                position i(x,y);
                accum.append(1,getChar(i));
                if(0==x&&0==y)
                    center=position(trposx,trposy);
                if(y+1<=maxY)
                    accum.append(1,',');
            }
            trposx=0;
            accum.append(1,'\n');
            trposy++;
        }
       // char ins[20];
       // sprintf(ins,"#dig\n",center.x,center.y);
       // string i(ins);
       // accum.insert(0,i);
        return accum;
    }
    void print_size()const{
        cout<<"("<<abs(minX)+maxX<<","<<abs(minY)+maxY<<")\n";
    }
    //Turn it into a CSV object with a few extra capabilities, and a much
    //better means for aliasing larger sizes of blocks
    csv toCSV(unsigned int block_size=1)const{
        csv i;
        for(auto c:this->content){
            string d=string(1,c.second);
            i.set_block(c.first.x,c.first.y,block_size,d);
        }
        return i;
    }
};

void draw_h_tree(grid& b,int initial_size,char d){
    list<pair<position,pair<int,bool> > > h;
    h.push_back(make_pair(position(0,0),make_pair(initial_size,true)));
    while(!h.empty()){
        position q=h.front().first;
        int size=h.front().second.first;
        bool vert=h.front().second.second;
        h.pop_front();
        if(!vert){
            auto i=make_pair(b.drawHLine(q,size,d,true),
                    make_pair(floor(size/reduction),true));
            auto j=make_pair(b.drawHLine(q,size,d,false),
                    make_pair(floor(size/reduction),true));
            if(floor(size/reduction)>2){
                h.push_back(i);
                h.push_back(j);
            }
        }else{
            auto i=make_pair(b.drawVLine(q,size,d,true),
                    make_pair(floor(size/reduction),false));
            auto j=make_pair(b.drawVLine(q,size,d,false),
                    make_pair(floor(size/reduction),false));
            if(floor(size/reduction)>1){
                h.push_back(i);
                h.push_back(j);
            }
        }
    }
}

int main(int argc,char **argv){
    int size=25;
    if(argc>1)
        size=atoi(argv[1]);
    grid i;
    draw_h_tree(i,size,'d');
    i.addChar(position(0,0),'i');
    cout<<i.toCSV().getContents()<<"\n";
    //i.print_size();
    return 0;
}
