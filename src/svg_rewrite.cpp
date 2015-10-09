#include "turtle.hpp"
#include "svg.hpp"
#include "json/json.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <unistd.h>
using namespace std;
enum operation{
  forward=0,
  turn_left=1,
  turn_right=2,
  push=3,
  pop=4
};
map<char, string> rewrites={{'0',"1[l0]r0"},{'1',"11"}};
map<char, operation> constants={
  {'0',operation::forward},
  {'1',operation::forward},
  {'[',push},
  {']',pop},
  {'l',turn_left},
  {'r',turn_right}
};
string read_file(const string& filename,double &angle_l,double &angle_r,double &forward_amount);
string rewrite(int iteration,const string& start);
int main(int argc,char **argv){
  double angle_l=45,
    angle_r=45;
  double f_step=5;
  string axiom="0";
  int c,iterations=8;
  string readfile,outfile;
  while((c=getopt(argc,argv,"r:o:i:"))!=-1){
    switch(c){
    case 'r':
      readfile=optarg;
      axiom=read_file(readfile,angle_l,angle_r,f_step);
      break;
    case 'o':
      outfile=optarg;
      break;
    case 'i':
      iterations=stoi(string(optarg));
      break;
    }
  }
  string result=rewrite(iterations,axiom);
  cursor current;
  svg s;
  path* p=s.beginPath();
  p->moveTo(current.x,current.y);
  double min_x=0,max_x=0,min_y=0,max_y=0;
  vector<cursor> stack;
  for(auto i : result){
    if(constants.find(i)==constants.end())
      continue;
    if(current.x>max_x)max_x=current.x;
    else if(current.x<min_x)min_x=current.x;
    if(current.y>max_y)max_y=current.y;
    else if(current.y<min_y)min_y=current.y;
    switch(constants.find(i)->second){
    case operation::forward:
      current=current.forward(f_step);
      p->lineTo(current.x,current.y);
      break;
    case turn_left:
      current.left(angle_l);
      break;
    case turn_right:
      current.right(angle_r);
      break;
    case push:
      stack.push_back(current);
      break;
    case pop:
      current=stack.back();
      stack.pop_back();
      p->moveTo(current.x,current.y);
      break;
    }
  }
  stringstream f;
  f<<min_x<<" "<<min_y<<" "<<max_x-min_x<<" "<<max_y-min_y;
  s.set_attribute("viewBox",f.str());
  s.set_attribute("preserveAspectRatio","xMidyMid");
  ofstream quip(outfile);
  quip<<s.serialize();
  quip.close();
}
string rewrite(int iteration,const string& start){
  stringstream eff;
  string cur=start;
  while(iteration>0){
    for(auto i : cur){
      if(rewrites.find(i)!=rewrites.end())
	eff<<rewrites[i];
      else
	eff<<i;
    }
    cur=eff.str();
    eff.str("");
    --iteration;
  }
  cout<<cur<<endl;
  return cur;
}
string read_file(const string& filename,double &angle_l,double &angle_r,double &forward_amount){
  constants.clear();
  rewrites.clear();
  Json::Value root;
  ifstream in(filename);
  in>>root;
  in.close();
  angle_l=root["left turn"].asDouble();
  angle_r=root["right turn"].asDouble();
  forward_amount=root["forward step"].asDouble();
  const Json::Value Constants=root["Constant"];
  const Json::Value rw=root["Rewrites"];
  const Json::Value axiom=root["Axiom"];
  auto const_names= Constants.getMemberNames();
  auto rw_names=rw.getMemberNames();
  for(string i : const_names){
    constants[i[0]]=(operation)Constants[i].asInt();
  }
  for(string i : rw_names){
    rewrites[i[0]]=rw[i].asString();
  }
  return axiom.asString();
}
