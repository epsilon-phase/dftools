#include "turtle.hpp"
#include "svg.hpp"
#include "json/json.h"
#include "csv.h"
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
map<char,operation> constants={
  {'0',operation::forward},
  {'1',operation::forward},
  {'[',push},
  {']',pop},
  {'l',turn_left},
  {'r',turn_right}
};
struct custom_oper{
  operation type;
  double argument=0.0;
};
map<int,vector<custom_oper> > custom_operations;
string read_file(const string& filename,double &angle_l,double &angle_r,double &forward_amount);
string rewrite(int iteration,const string& start);
int main(int argc,char **argv){
  double angle_l=45,
    angle_r=45;
  double f_step=5;
  string axiom="0";
  int c,iterations=8;
  string readfile,outfile;
  bool csvmode=false;
  string csvfile;
  while((c=getopt(argc,argv,"r:o:i:c:"))!=-1){
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
    case 'c':
      csvmode=true;
      csvfile=optarg;
      break;
    }
  }
  csv* c_out=NULL;
  if(csvmode)c_out=new csv();
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
      {
	cursor tmp=current.forward(f_step);
	if(c_out)
	  c_out->linefrom(current.x,current.y,tmp.x,tmp.y,"d");
	current=tmp;
	p->lineTo(current.x,current.y);
      }
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
    default://used to implement custom operations with custom arguments
      if(custom_operations.find(constants.find(i)->second)!=custom_operations.end()){
	cout<<"Found custom operation\n";
	const vector<custom_oper>& e=custom_operations[constants.find(i)->second];
	for(auto j : e){
	  switch(j.type){
	  case operation::forward:
	    {
	      double f_temp=f_step*j.argument;
	      cursor tmp=current.forward(f_temp);
	      if(c_out)
		c_out->linefrom(current.x,current.y,tmp.x,tmp.y,"d");
	      current=tmp;
	      p->lineTo(current.x,current.y);
	    }
	    break;
	  case turn_left:
	    current.left(j.argument!=0.0?j.argument:angle_l);
	    break;
	  case turn_right:
	    current.right(j.argument!=0.0?j.argument:angle_r);
	    break;
	  case push:
	    stack.push_back(current);
	    break;
	  case pop:
	    current=stack.back();
	    stack.pop_back();
	    break;
	  }
	}
      }
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
  if(c_out)
    c_out->writeToFile(csvfile);
  return 0;
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
  if(root.isMember("Custom Operations")){
    const Json::Value cust_op=root["Custom Operations"];
    auto cust_op_mem=cust_op.getMemberNames();
    for(string j:cust_op_mem){
      if(!cust_op[j].isArray()){
	//do something about the error
      }
      int current_op=stoi(j);
      vector<custom_oper> f_eq;
      for(Json::Value cur_op:cust_op[j]){
	if(cur_op.isObject()){
	  cout<<cur_op<<endl;
	  custom_oper f;
	  f.type=(operation)cur_op["t"].asInt();
	  f.argument=cur_op["val"].asDouble();
	  f_eq.push_back(f);
	}else if(cur_op.isIntegral()){
	  custom_oper f;
	  f.type=(operation)cur_op.asInt();
	  f.argument=0;
	  f_eq.push_back(f);
	}else{
	  //another error, what to do?
	}
      }
      custom_operations[current_op]=f_eq;
    }
  }
  return axiom.asString();
}
