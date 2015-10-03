#include "csv.h"
#include <tuple>
#include <unistd.h>
#include <set>
using namespace std;
int main(int argc,char** argv){
  int c;
  std::string iname,oname;
  while((c=getopt(argc,argv,"i:o:"))!=-1){
    switch(c){
    case 'i':
      iname=optarg;
      break;
    case 'o':
      oname=optarg;
      break;
    }
  }
  csv f;
  std::map<std::string,std::tuple<int,int,int> > cmap;
  f.readFromFile(iname);
  tuple<int,int,int> e;
  std::cout<<f.get_extant().size()<<endl;
  for(auto c : f.get_extant()){
  cout<<c;
  cin>>get<0>(e)>>get<1>(e)>>get<2>(e);
  cmap[c]=e;
}
  f.writeAsPPM(oname,cmap);
}
