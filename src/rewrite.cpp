#include "csv.h"
#include <iostream>
#include <map>
#include <string>
#include <functional>
#include <vector>
#include <fstream>
#include <list>
#include "turtle.hpp"
#include <unistd.h>
#include "json/json.h"
using namespace std;
enum{
  FORWARDS=0,
  PUSH=1,
  POP=2,
  TURN_LEFT=3,
  TURN_RIGHT=4
};
struct operation{
  int optype,op_args;
};
typedef vector<operation> constant;
map<char,constant> Constants;//the "primitive" operations
map<char,string> Rewrite_rules;//the rules that REWRITE
string axiom;//the starting string
int scale=3;//the scale of each forward movement

void evaluate(csv&input,int iterations,const string& current){
  string next;
  if(iterations>0){
    for(char c : current){
      if(iterations > 0){
	if(Rewrite_rules.find(c) == Rewrite_rules.end()){
	  next.push_back(c);//maybe constant without rule
	}else{
	  next.append(Rewrite_rules.find(c)->second);//rewrite rule for sure, maybe operation, but not now
	}
      }
    }
    evaluate(input,iterations-1,next);
  }else{
    cout<<"Final string"<<endl<<current<<endl;
    cursor initial;
    vector<cursor> stack;
    for(int c=0 ; c < current.size(); ++c){
      if(Constants.find(current[c])==Constants.end())
	continue;
      constant current_op = Constants[ current[ c ] ];
      for(int i=0;i < current_op.size();i++){
	switch(current_op[i].optype){
	case FORWARDS:
	  {
	  cursor tmp=initial.forward(scale);
	  input.linefrom(floor(tmp.x),floor(tmp.y),floor(initial.x),floor(initial.y),"d");
	  initial=tmp;
	  }
	  break;
	case TURN_LEFT:
	  initial.left(current_op[i].op_args);

	  
	  break;
	case TURN_RIGHT:
	  initial.right(current_op[i].op_args);
	  break;
	case PUSH:
	  stack.push_back(initial);
	  break;
	case POP:
	  initial=stack.back();
	  stack.pop_back();
	  break;
	}
      }
    }
  }
}
void read_file(const string& filename){
  Json::Value root;
  ifstream e(filename);
  e>>root;
  const Json::Value constants=root["Constant"];
  const Json::Value rewrites=root["Rewrite"];
  const Json::Value axom = root["Axiom"];
  cout<<"Found "<<constants.size()<<" rules"<<endl;
  for(int i=0; i < constants.size();i++){
    char key=constants[i].get("key","").asCString()[0];
    const Json::Value a=constants[i],operations=a["value"];
    constant f;
    for(int j=0;j<operations.size();j++){
      operation o;o.optype= operations[j].get("op_type",0).asInt();
      o.op_args=operations[j].get("op_args",0).asInt();
      f.push_back(o);
    }
    Constants[key]=f;
  }
  for(int i=0;i<rewrites.size();i++){
    const Json::Value c=rewrites[i];
    char key=c.get("key","").asCString()[0];
    string f=c.get("value","").asString();
    Rewrite_rules[key]=f;
  }
  axiom=axom.asString();
  e.close();
}
void print_help(int argc,char **argv);
int main(int argc, char** argv){
  int c;
  int iterations=4;
  string output;
  bool make_picture=false;
  string pict;
  scale=4;
  while((c=getopt(argc,argv,"i:r:o:s:p:?"))!=-1){
    switch(c){
    case 'i':
      {
	if(optarg!=NULL){
	string tmp=string(optarg);
      iterations = stoi(tmp);
	}
      }
      break;
    case 'r':
      if(optarg!=NULL){
	read_file(string(optarg));
      }
      break;
    case 'o':
      output= string(optarg);
      break;
    case '?':
      print_help(argc,argv);
      break;
    case 's':
      {
	string g(optarg);
	scale=stoi(g);
      }
      break;
    case 'p':
      pict=optarg;
      make_picture=true;
      break;
    default:
      print_help(argc,argv);
    }
  }
  csv out;
  out.recording=true;
  evaluate(out,iterations,axiom);
  out.writeToFile(output);
  if(make_picture){
    ofstream fc(pict);
    auto dim=out.getDim();
    fc<<"<svg  xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">"<<endl;
    fc<<"<rect x=\""<<dim[0]<<"\" y=\""<<dim[1]<<"\" width=\""<<out.width()<<"\" height=\""<<out.height()<<"\"/>";
    for(auto q : out.stuff){
      fc<<"<polyline points=\""<<q[0]<<","<<q[1]<<","<<q[2]<<","<<q[3]<<"\" stroke=\"black\"/>"<<endl;
    }
    fc<<"</svg>";
  }
  std::cout<<out.width()<<" "<<out.height()<< endl;
}
void print_help(int argc,char **argv){
  cout<<"Proper usage is \""<<argv[0]<<"-i <integer> -r <input file> -o <output file>"<<endl;
}
