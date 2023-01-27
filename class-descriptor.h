#ifndef CLASS_DESCRIPTOR_H
#define CLASS_DESCRIPTOR_H
#include "attribute-descriptor.h"
#include <string>
#include <vector>
using namespace std;

enum classNonAccessModifier {
  CLASS_FINAL,
  CLASS_ABSTRACT,
};

class ClassDescriptor {
private:
  string name{};
  bool publicClass;
  classNonAccessModifier nonAccessModifier;
  bool mainFunction;
  vector<AttributeDescriptor> attributes{};
  //generate attributesContent
  string generateAttributesStr();
  //generate constructor
  string generateConstructor();
  //Generate getter
  string generateGetters();
  //Generate setter
  string generateSetters();

public:
  //Constructeur
  ClassDescriptor(string name, bool publicClass, classNonAccessModifier nonAccessModifier, bool mainFunction);
  //Constructeur without non access descriptor
  ClassDescriptor(string name, bool publicClass, bool mainFunction);
  //getter name
  string getName();
  //Add attribute
  void addAttribute(attributeAccessModifier accessModifier, attributeNonAccessModifier nonAccessModifier, string type, string name, attributeAccessModifier getter, attributeAccessModifier setter, bool inConstructor);
  //generate .java class file
  string generate();
};

#endif
