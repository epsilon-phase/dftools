#include "reaction.hpp"
/**
 *Item token print here
 */
void item_token::print(std::ostream& o)const{
  o<< type+" "+subtype<<std::endl;
}
  
/**
 *material things here
 */
material_token::material_token(Reaction* r):parent(r){}
material_token::~material_token(){}
void material_token::print(std::ostream& o)const{
  o<< get_Type()+" "+get_Sub()<<std::endl;
}
derived_mat::derived_mat(const std::string& r_id, Reaction *r):material_token(r),r_id(r_id){}
derived_mat::~derived_mat(){}
void derived_mat::print(std::ostream& o)const{
  o<<get_Type()+" "+get_Sub()<<std::endl;
}
std::string derived_mat::get_Type()const{
  return parent->name_mappings[r_id]->mat->get_Type();
}
std::string derived_mat::get_Sub()const{
  return parent->name_mappings[r_id]->mat->get_Sub();
}
known_mat::known_mat(const std::string& type, const std::string& sub,Reaction* i):material_token(i),type(type),sub(sub){
}
known_mat::~known_mat(){
}
std::string known_mat::get_Type()const{
  return type;
}
std::string known_mat::get_Sub()const{
  return sub;
}
void known_mat::print(std::ostream& o)const{
  o<<type<<" "<<sub<<std::endl;
}
/**
 *ProductModifier things here
 */
ProductModifier::ProductModifier(const std::string& n,Product *parent):parent(parent),name(n){}
void ProductModifier::affect_product()const{}
void ProductModifier::print(std::ostream& o)const{
  o<<name<<std::endl;
}
ToContainer::ToContainer(const std::string &name, const std::string& container_id,Product* p):ProductModifier(name,p),container_id(container_id){}
void ToContainer::print(std::ostream& o)const{
  o<<name<<" "<<container_id<<std::endl;
}
/**
 *Reagent stuff here
 */

Reagent::Reagent(){}
Reagent::Reagent(Reaction* p,const RawTag& tag):parent(p){
  this->name=tag.tagvalues[0];
  this->quantity=std::stoi(tag.tagvalues[1]);
  item_token it;
  it.type=tag.tagvalues[2];
  it.type=tag.tagvalues[3];
  mat=new known_mat(tag.tagvalues[4],tag.tagvalues[5],parent);
}
Reagent::~Reagent(){
  delete mat;
  for(auto i:modifiers)
    delete i;
}
void Reagent::print(std::ostream& o)const{
  o<<"\t\t\t"<<name<<std::endl;
  o<<"\t\t\t"<<quantity<<std::endl;
  o<<"\t\t\t\t";
  tok.print(o);
  o<<"\t\t\t\t";
  mat->print(o);
  for(auto i : modifiers){
    o<<"\t\t\t\t";
    i->print(o);
  }
}
/**
 *Reaction stuff
 */
Reaction::Reaction(){}
Reaction::Reaction(const std::vector<RawTag>& tags){
  const RawTag& first = tags[0];
  this->id=first.tagvalues[0];
  bool wasReagent=false;
  Reagent *lastReagent=NULL;
  Product *lastProduct=NULL;
  for(int i=1;i<tags.size();++i){
    const RawTag& tag=tags[i];
    if(tag.tagname=="NAME"){
      name=tag.tagvalues[0];
    }else
      if(tag.tagname=="BUILDING"){
	ReactionBuilding e;
	e.name=tag.tagvalues[0];
	e.key=tag.tagvalues[1];
	this->building=e;
      }else if(tag.tagname=="SKILL"){
	this->skill=tag.tagvalues[0];
      }else if(tag.tagname=="FUEL"){
	fuel=true;
      }else if(tag.tagname=="REAGENT"){
	Reagent *temp=new Reagent(this,tag);
	this->reagents.push_back(temp);
	this->name_mappings[temp->name]=temp;
	lastReagent=temp;
	wasReagent=true;
      }else if(tag.tagname=="PRODUCT"){
	Product *temp=new Product(this,tag);
	products.push_back(temp);
	lastProduct=temp;
	wasReagent=false;
      }else if(tag.tagname=="ADVENTURE"){
	adventure=true;
      }else if(tag.tagname=="AUTOMATIC"){
	automatic=true;
      }else{
	if(wasReagent&&lastReagent){
	  ReagentModifier *temp;
	  if(tag.tagvalues.empty()){
	    temp=new ReagentModifier(tag.tagname,lastReagent);
	  }else{
	    temp=new TwoPartMod(tag.tagname,tag.tagvalues[0],lastReagent);
	  }
	  lastReagent->modifiers.push_back(temp);
	}else if(lastProduct){
	  ProductModifier* temp;
	  if(tag.tagvalues.empty()){
	    temp = new ProductModifier(tag.tagname,lastProduct);
	  }else{
	    temp=new ToContainer(tag.tagname,tag.tagvalues[0],lastProduct);
	  }
	  lastProduct->modifiers.push_back(temp);
	}
      }
  }
}
Reaction::~Reaction(){
  for(auto i : reagents)
    delete i;
  for(auto i : products)
    delete i;
}
void Reaction::print(std::ostream& o)const{
  o<<"Reaction:"<<id<<"("<<name<<")"<<std::endl;
  o<<"\t"<<building.name<<std::endl;
  o<<"\t"<<building.key<<std::endl;
  o<<"\t"<<(fuel?"Requires fuel":"Requires no fuel")<<std::endl;
  o<<"\t"<<(automatic?"Occurs automatically":"Requires manual assignment")<<std::endl;
  o<<"\t"<<(adventure?"Meant for adventure mode":"Meant for fortress mode")<<std::endl;
  o<<"\t"<<"REAGENTS:"<<std::endl;
  for(auto i : reagents)
    i->print(o);
  o<<"\t"<<"PRODUCTS:"<<std::endl;
  for(auto i : products)
    i->print(o);
}
/**
 *Product stuff here
 */

Product::Product(){}
Product::Product(Reaction *p,const RawTag& tag){
  const std::vector<std::string>& values=tag.tagvalues;
  probability = std::stoi(values[0]);
  quantity = std::stoi(values[1]);
  item.type=values[2];
  item.subtype=values[3];
  if(values[4]=="GET_MATERIAL_FROM_REAGENT"){
     material=new derived_mat(values[5],p);
  }else{
    material =new known_mat(values[4],values[5],p);
  }
}
Product::~Product(){
  delete material;
  for(auto i : modifiers)
    delete i;
}
void Product::print(std::ostream& o)const{
  o<<probability<<" out of 100 chance to produce "<<quantity<<"units of"<<std::endl;
  o<<"\t\t\t";
  item.print(o);
  o<<std::endl;
  o<<"\t\t\t";
  material->print(o);
  o<<std::endl;
  for(auto i : modifiers){
    o<<"\t\t\t\t";
    i->print(o);
    o<<std::endl;
  }
}
/**
 *Reagent modifier stuff
 */
ReagentModifier::ReagentModifier(const std::string& first,Reagent* par):parent(par),first(first){}

TwoPartMod::TwoPartMod(const std::string& first,const std::string& second,Reagent* par):ReagentModifier(first,parent),second(second){}
void ReagentModifier::print(std::ostream& o)const{
  o<<first<<std::endl;
}
void TwoPartMod::print(std::ostream& o)const{
  o<<first<<" "<<second<<std::endl;
}
