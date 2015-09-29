#ifndef REACTION_HPP
#define REACTION_HPP
#include "raw_reader.hpp"
#include <iostream>
#include <map>
struct item_token{
  std::string type,subtype;
  void print(std::ostream&)const;
};
struct material_token;
struct Reagent;
struct ReagentModifier;
struct Product;
struct ProductModifier;
struct ReactionBuilding{
  std::string name;
  std::string key;
};
class Reaction{
public:
  Reaction();
  Reaction(const std::vector<RawTag>&);
  ~Reaction();
  void print(std::ostream&)const;
  std::string id;
  std::string name;
  std::string skill;
  bool fuel=false,automatic=false,adventure=false;
  ReactionBuilding building;
  std::map<std::string,Reagent*> name_mappings;
  std::vector<Reagent*> reagents;
  std::vector<Product*> products;
};
struct Product{
  Product();
  Product(Reaction*,const RawTag&);
  ~Product();
  material_token* material;
  item_token item;
  int quantity;
  int probability;
  std::vector<ProductModifier*> modifiers;
  void print(std::ostream&)const;
private:
  Reaction* parent;
};

struct Reagent{
  Reagent();
  Reagent(Reaction*,const RawTag&);
  ~Reagent();
  std::string name;
  int quantity;
  item_token tok;
  material_token* mat;
  std::vector<ReagentModifier*> modifiers;
  void print(std::ostream& o)const;
private:
  Reaction* parent;
};
struct material_token{
  material_token(Reaction*);
  ~material_token();
  virtual std::string get_Type()const=0;
  virtual std::string get_Sub()const=0;
  virtual void print(std::ostream&)const;
protected:
    Reaction* parent;
};
struct derived_mat:public material_token{
  derived_mat(const std::string& reagent_id, Reaction* r);
  ~derived_mat();
  std::string get_Type()const;
  std::string get_Sub()const;
  void print(std::ostream&)const;
private:
  std::string r_id;
};
struct known_mat:public material_token{
  known_mat(const std::string& type,const std::string& sub, Reaction* i);
  ~known_mat();
  std::string get_Type()const;
  std::string get_Sub()const;
  void print(std::ostream&)const;
private:
  std::string type,sub;
};
struct ProductModifier{
  ProductModifier(const std::string& name, Product *parent);
  std::string name;
  virtual void print(std::ostream&)const;
  //normally it doesn't matter
  virtual void affect_product()const;
protected:
  Product* parent;
};
struct ToContainer:public ProductModifier{
  ToContainer(const std::string& name, const std::string& container_id,Product* p);
  std::string container_id;
  void print(std::ostream&)const;
};
struct ReagentModifier{
  ReagentModifier(const std::string& first,Reagent* par);
  std::string first;
  virtual void print(std::ostream&)const;
protected:
  Reagent* parent;
};
struct TwoPartMod:public ReagentModifier{
  TwoPartMod(const std::string&, const std::string& second,Reagent* p);
  std::string second;
  void print(std::ostream&)const;
};
#endif
