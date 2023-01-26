#include "class-descriptor.h"
#include "attribute-descriptor"
#include <string>
#include <vector>

//Constructeur
ClassDescriptor::ClassDescriptor(string name, bool public, nonAccessModifier nonAccessModifier, bool mainFunction) {
  this->name = name;
  this->public = public;
  this->nonAccessModifier = nonAccessModifier;
  this->mainFunction = mainFunction;
}

//Constructeur without non access descriptor
ClassDescriptor::ClassDescriptor(string name, bool public, bool mainFunction) {
  this->name = name;
  this->public = public;
  this->nonAccessModifier = NULL;
  this->mainFunction = mainFunction;
}

//getter name
string ClassDescriptor::getName() {
  return this->name;
}

//Add attribute
void ClassDescriptor::addAttribute(string name, AttributeAccessModifier accessModifier, bool write, bool read, attributeNonAccessModifier nonAccessModifier) {
  this->attributes.push_back(AttributeDescriptor{name, accessModifier, write, read, nonAccessModifier});
}

//Generate .java class file
string ClassDescriptor::generate() {
  string fileContent{};
  //check if class is public
  if (this->public) {
    fileContent += "public ";
  }
  //add class name
  fileContent += "class " + this->name + " {\n\t\n}";

}
