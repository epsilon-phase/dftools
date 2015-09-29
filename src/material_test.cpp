#include "material.hpp"
#include <iostream>
using namespace std;

int main(){
  auto qq= RawReader::ReadFile("raw/objects/inorganic_metal.txt");
  cout<<"Finished reading file\n";
  vector<DFObject*> things;
  DFObject *current=NULL;
  if(qq.empty()){
    cout<<"Nothing was read :'(\n";
  }
  for(int i=0;i < qq.size(); ++i){
    if(qq[i].tagname == "INORGANIC"){
      if(current)
      things.push_back(current);
      current=new Material();
    }else{
      if(current&&!current->consumeTag(qq[i])){
	cout<<"Did not match with tagname "<<qq[i].tagname<< (qq[i].tagvalues.size()>0?" with values :":"")<<endl;
	for(auto z : qq[i].tagvalues){
	  cout<<"\t"<<z<<endl;
	}
      }
    }
  }
  
}
