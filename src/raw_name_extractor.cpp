#include "raw_reader.hpp"
#include <unordered_set>
#include <iostream>
using namespace std;
int main(int argc,char** argv){
  unordered_set<string> tagnames;
  for(int z=1;z<argc;z++){
  string filename=argv[z];
  auto tags=RawReader::ReadFile(filename);
  cerr<<" "<<filename<<endl<<endl;
  for(auto i : tags){
    tagnames.insert(i.tagname);
  }
  int count=0;
  for(auto i : tagnames){
    cout<<"\""<<i<<"\""<<(count<tagnames.size()-1?",":"");
    count++;
  }
  }
  cout<<endl<<endl;
  return 0;
}
