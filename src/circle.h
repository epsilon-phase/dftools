#ifndef CIRCLE_H
#define CIRCLE_H
#include <cmath>
#include "csv.h"
#include <string>
inline float sqr(float x){
    return x*x;
}

inline float distance(int x0,int y0,int x1,int y1){
    return std::sqrt(sqr(x1-x0)+sqr(y1-y0));
}
void midpoint(int x0,int y0, int radius,
        unsigned int block_size,
        const std::string &fuffle,csv &q){
    int x=radius,y=0;
    int radiuserror=1-x;
    while(x>=y){
        if(block_size<=1){
            q.setCell(x+x0,y+y0,fuffle);
            q.setCell(y+x0,x+y0,fuffle);
            q.setCell(-x+x0,y+y0,fuffle);
            q.setCell(-y+x0,x+y0,fuffle);
            q.setCell(-x+x0,-y+y0,fuffle);
            q.setCell(-y+x0,-x+y0,fuffle);
            q.setCell(x+x0,-y+y0,fuffle);
            q.setCell(y+x0,-x+y0,fuffle);
        }else{
            q.set_block(x+x0,y+y0,block_size,fuffle);
            q.set_block(y+x0,x+y0,block_size,fuffle);
            q.set_block(-x+x0,y+y0,block_size,fuffle);
            q.set_block(-y+x0,x+y0,block_size,fuffle);
            q.set_block(-x+x0,-y+y0,block_size,fuffle);
            q.set_block(-y+x0,-x+y0,block_size,fuffle);
            q.set_block(x+x0,-y+y0,block_size,fuffle);
            q.set_block(y+x0,-x+y0,block_size,fuffle);
        }
        y++;
        if(radiuserror<0)
            radiuserror+=2*y+1;
        else
        {
            x--;
            radiuserror+=2*(y-x+1);
        }
    }
}
void fill_circle(int x0,int y0,int radius,unsigned int block_size, const std::string &fuffle,csv &input){
   for(int mx=x0-radius;mx<=x0+radius+1;mx++){
       for(int my=y0-radius;my<=y0+radius+1;my++){
           if(distance(mx,my,x0,y0)<=radius){
               if(block_size<=1)
                   input.setCell(mx,my,fuffle);
               else
                   input.set_block(mx,my,block_size,fuffle);
           }
       }
   }
   if(block_size<=1)
       input.setCell(x0+radius+1,y0,fuffle);
   else
       input.set_block(x0+radius+1,y0,block_size,fuffle);
}
#endif
