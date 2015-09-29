#include "circle.h"
#include <iostream>
#include <fstream>
#include <unistd.h>
using namespace std;
//create a single empty ring
void single_ring(csv& input,
        unsigned int thickness,
        unsigned int radius,
        bool stairs=true,
        const std::string &fuffle="d",
        unsigned int bsize=1){
    //draw stairs around the perimeter
    if(stairs){
        fill_circle(0,0,thickness+radius,bsize,"i",input);
        fill_circle(0,0,thickness+radius-1,bsize,fuffle,input);
    }else//or not
        fill_circle(0,0,thickness+radius,bsize,fuffle,input);
    //erase the center
    midpoint(0,0,radius,bsize," ",input);
}
void concentric(csv& input,unsigned int thickness, unsigned int layers, bool alternate=true,
        const std::string &fuffle="d",
        bool drawstairs=true,
        int cx=0,
        int cy=0,
        bool bullseye=true)
{
    int outerradius;
    if(alternate){
        outerradius=2*thickness*layers;
    }else
        outerradius=thickness*layers;
    for(outerradius=outerradius;outerradius>0;){
        single_ring(input,thickness,outerradius-thickness,true,fuffle,1);
        if(alternate)
            outerradius-=thickness;
        outerradius-=thickness;
    }
    outerradius=thickness*layers;
    if(alternate)
        outerradius*=2;
    if(bullseye){
        input.linefrom(cx,cy,  cx-outerradius,cy,fuffle);
        input.linefrom(cx,cy,    cx+outerradius,cy,fuffle);
        input.linefrom(cx,cy,cx, cy+outerradius,fuffle);
        input.linefrom(cx,cy,cx,cy-outerradius,fuffle);
    }
}
void usage(const char * name){
    cout<<"-r <number> radius increase\n"
        <<"-l <number> layer count\n"
        <<"-o <output file> specifies the file which you wish to output to.\n"
        <<"-c <string> Specifies the command to give.\n";
    exit(0);
}
int main(int argc,char **argv){
    csv i;
int c,
        radius=12,
        layers=2;
    string command="d";
    ofstream q;
    while((c=getopt(argc,argv,"r:l:o:c:h"))!=-1){
        switch(c){
            case 'c':
                command=optarg;
                break;
            case 'l':
                layers=atoi(optarg);
                break;
            case 'r':
                radius=atoi(optarg);
                break;
            case 'o':
                q.open(optarg);
                break;
            case 'h':
                usage(argv[0]);

        }
    }
    if(!q.is_open())
        q.open("concentric.csv");

    concentric(i,radius,layers,true,command,true);
    q<<i.getContents();
    cout<<i.getContents();
}
