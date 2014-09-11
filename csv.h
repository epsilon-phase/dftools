#ifndef CSV_H
#define CSV_H
#include <string>
#include <map>
#include <cmath>
#include <fstream>
#include <iostream>
#ifdef DEBUG
#include <iostream>
#endif
class csv{
    std::map<int,std::map<int,std::string> > content;
    int block_size;
    int hc,lc,hr,lr;
    public:
    csv():hc(0),lr(0),lc(0),hr(0),block_size(1){}
    ~csv(){}
    //Set the content of a cell in the CSV
    void setCell(int x,int y,const std::string &i){
        content[y][x]=i;

        //Check for a new maximum bounds and update.
        if(hc<x)
            hc=x+1;
        else if (lc>x)
            lc=x;
        if(lr>y)
            lr=y;
        else if(hr<y)
            hr=y;
    }
    //Get the content of a cell, or return ' '
    std::string getCell(int x,int y)const{
        if(content.find(y)!=content.end())
        {
            auto cc=content.find(y)->second;
            if(cc.find(x)!=cc.end())
                return cc[x];
        }
        return " ";
    }
    //get a row of a CSV file
    std::string getLine(int y)const{
        std::string i;
        for(int c=lc;c<hc;c++){
            i+=getCell(c,y);
            if(c+1<hc)
                i+=",";
        }
        return i;
    }
    void readFromFile(const std::string &input,bool center=false){
        //Clear the existing information, should there be any.
        this->content.clear();
        std::ifstream q;
        q.open(input);
        int row=0,column=0;
        char current;
        while(!q.eof()){
            std::string accumulated;
            q.read(&current,1);
            if(current==','){
                setCell(column,row,accumulated);
                //increment the column count
                column++;
                //reset the string
                accumulated="";
            }else if(current=='\n'){
                setCell(column,row,accumulated);
                //increment the row
                row++;
                //reset the column count
                column=0;
                accumulated=""; 
            }else{
                accumulated+=current;
            }
    }
    }
    void writeToFile(const std::string& output)const{
        std::ofstream i;
        i.open(output);
        i<<getContents();
        i.close();
    }
    //Get the entire file mostly correctly formatted.
    std::string getContents() const{
#ifdef DEBUG
        std::cerr<<"Creating string\n";
#endif
        std::string c;
        for(int i=lr;i<=hr;i++){
            //add a newline
            c+=getLine(i)+"\n";
        }
        //Yay string!
#ifdef DEBUG
        std::cerr<<"Finished making string\n";
#endif
        return c;
    }
    //simulate a grid with less granularity(E.G. make a single tile designation
    //take up multiple tiles).
    void set_block(int x,int y,unsigned int block_size, const std::string& stuff){
        if(block_size==1)
            //Not so exciting
            this->setCell(x,y,stuff);
        else
            for(int i=0;i<block_size;i++){
                for(int z=0;z<block_size;z++){
                    //Yay Cells
                    this->setCell(x*block_size+i,y*block_size+z,stuff);
                }
            }
    }
    void linefrom(int x1,int y1,int x2,int y2,
            const std::string &fil,unsigned int b_size=1){
        using namespace std;
        bool steep=abs(y2-y1)>abs(x2-x1);
        if(steep)
        {
            swap(x1,y1);
            swap(x2,y2);
        }
        if(x1>x2)
        {
            swap(x1,x2);
            swap(y1,y2);
        }
        int deltax=x2-x1;
        int deltay=abs(y2-y1);
        int error=deltax/2;
        int ystep;
        int y=y1;
        if(y1<y2)
            ystep=1;
        else
            ystep=-1;
        for(int x=x1;x<=x2;x++){
            if(steep)
            {
                if(b_size==1)
                    setCell(y,x,fil);
                else
                    set_block(y,x,b_size,fil);
            }else
            {
                if(b_size==1)
                    setCell(x,y,fil);
                else
                    set_block(x,y,b_size,fil);
            }
            error=error-deltay;
            if(error<0){
                y=y+ystep;
                error=error+deltax;
            }
        }
    }
};
#endif
