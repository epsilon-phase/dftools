#include "raw_reader.hpp"
#include <iostream>
using namespace std;
int main(int argc,char **argv){
  std::string file;
  if(argc==2)
    file=argv[1];
  else
    file="example.txt";
  std::vector<RawTag> e=RawReader::ReadFile(file);
  for(auto i:e){
    cout<<i.tagname<<endl;
    for(std::string tagval:i.tagvalues){
      cout<<"\t"<<tagval<<endl;
    }
    cout<<endl<<endl;
  }
    
}
