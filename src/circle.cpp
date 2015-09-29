#include "csv.h"
#include "circle.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <unistd.h>
#include <cstdlib>
using namespace std;
void usage(){
    cout<<"Usage:\n"
        <<"-c <command>\n"
        <<"-r <radius>\n"
        <<"-o <file>\n"
        <<"-f do not fill the circle\n";
    exit(0);
}
int main(int argc,char **argv){
    csv qw;
    int c,
        r=12;
    bool fillcircle=true;
    ofstream output;
    string command="d";
    while((c=getopt(argc,argv,"fo:c:r:h"))!=-1){
        switch(c){
            case 'h':
                usage();
                break;
            case 'r':
                r=atoi(optarg);
                break;
            case 'c':
                command=optarg;
                break;
            case 'o':
                output.open(optarg);
                break;
            case 'f':
                fillcircle=false;
                break;
        }
    }
    if(!output.is_open())
        output.open("circle.csv");
    if(fillcircle)
        fill_circle(0,0,r,1,command,qw);
    else
        midpoint(0,0,r,1,command,qw);
    output<<qw.getContents();
    cout<<qw.getContents();
    output.close();

    return 0;
}
