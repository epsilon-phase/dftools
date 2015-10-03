#ifndef DFOBJECT_HPP
#define DFOBJECT_HPP
#include "raw_reader.hpp"
enum DFType{
  none=0,
  material,
  plant,
  reaction,
  creature,
  item_weapon,
  item_toy,
  item_tool,
  item_instrument,
  item_ammo,
  item_armor,
  item_trapcomp,
  item_gloves,
  item_shoes,
  item_shield,
  item_helm,
  item_pants,
  item_food,
  body,
  entity,
  entity_position,
  word,
  tissue
};
class DFObject{
public:
  DFObject();
  virtual ~DFObject();
  virtual DFType getType()const{return none;}
  /**
   *Returns true if the object is capable of consuming the tag
   */
  virtual bool consumeTag(const RawTag&)=0;
  
};
#endif
