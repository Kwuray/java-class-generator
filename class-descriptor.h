#ifndef CLASS_DESCRIPTOR_H
#define CLASS_DESCRIPTOR_H
#include "attribute-descriptor.h"
#include <string>
#include <vector>

enum classNonAccessModifier {
  FINAL,
  ABSTRACT,
  NONE
};

class ClassDescriptor {
private:
  string name{};
  bool public;
  classNonAccessModifier nonAccessModifier;
  bool mainFunction;
  vector<AttributeDescriptor> attributes{};

public:
  //Constructeur
  ClassDescriptor(string name, bool public, classNonAccessModifier nonAccessModifier, bool mainFunction);
  //getter name
  string getName();
  //Add attribute
  void addAttribute(string name, AttributeAccessModifier accessModifier, bool write, bool read, attributeNonAccessModifier nonAccessModifier);
  //generate .java class file
  string generate();
  //Destructeur
  ~ClassDescriptor();

};

#endif
