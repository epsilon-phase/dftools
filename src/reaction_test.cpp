#include "reaction.hpp"
#include <fstream>

using namespace std;

int main(){
  std::string filename="reaction_example.txt";
  auto f=RawReader::ReadFile(filename);
  Reaction e(f);
  e.print(cout);
}
