#include "raw_reader.hpp"
#include <iostream>
#include <fstream>
std::vector<RawTag> RawReader::ReadFile(const std::string& file){
  std::vector<RawTag> f;
  std::ifstream reader(file);
  std::string cur;
  bool intag=false;
  int values_gotten=0;
  RawTag current;
  while(!reader.eof()){
    char c = reader.get();
    switch(c){
    case '[':
      cur="";
      intag = true;
      values_gotten = 0;
      break;
    case ']':
      if(!intag){
	std::cerr<<"Shitty raw formation. incorrect placement of ']'\r\n";
      }
      intag=false;
      if(values_gotten == 0){
	current.tagname = cur;
      }else{
	current.tagvalues.push_back(cur);
      }
      f.push_back(current);
      current=RawTag();//empty the current tag.
      break;
    case ':':
      if(!intag)
	break;
      if(values_gotten == 0){
	current.tagname = cur;
      }else{
	current.tagvalues.push_back( cur );
      }
      values_gotten++;
      cur = "";    
      break;
    default:
      if(intag)
	cur.push_back(c);//Don't bother recording things that aren't in the tags.
      break;
    }
  }
  return f;
}
