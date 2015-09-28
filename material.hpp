#ifndef MATERIAL_HPP
#define MATERIAL_HPP
#include <string>
#include "raw_reader.hpp"
#include <vector>
#include <map>
#include <unordered_set>
#include "dfobject.hpp"
/**
 *A class for representing the material entries of dwarf fortress.
 */
class Material:public DFObject{
protected:
  /**
   *Contains the list of tags that are allowable in the definition. Necessary for figuring out whether or not it should stop consuming input and attempt to identify the new object that is in the process of being defined.
   */
  static std::unordered_set<std::string> accepted_tag_names;
  std::vector<RawTag> tags;
  std::multimap<std::string,int> tag_indices;
public:
  DFType getType()const{return material;}
  virtual bool consumeTag(const RawTag&);
};
#endif
