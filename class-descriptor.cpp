#include "class-descriptor.h"
#include "attribute-descriptor.h"
#include <string>
#include <vector>
using namespace std;
using namespace std;

//Constructeur
ClassDescriptor::ClassDescriptor(string name, bool publicClass, classNonAccessModifier nonAccessModifier, bool mainFunction) {
  this->name = name;
  this->publicClass = publicClass;
  this->nonAccessModifier = nonAccessModifier;
  this->mainFunction = mainFunction;
}

//Constructeur without non access descriptor
ClassDescriptor::ClassDescriptor(string name, bool publicClass, bool mainFunction) {
  this->name = name;
  this->publicClass = publicClass;
  this->mainFunction = mainFunction;
}

//getter name
string ClassDescriptor::getName() {
  return this->name;
}

//Add attribute
void ClassDescriptor::addAttribute(attributeAccessModifier accessModifier, attributeNonAccessModifier nonAccessModifier, string type, string name, attributeAccessModifier getter, attributeAccessModifier setter, bool inConstructor) {
  this->attributes.push_back(AttributeDescriptor{accessModifier, nonAccessModifier, type, name, getter, setter, inConstructor});
}

//generate attributesContent
string ClassDescriptor::generateAttributesStr() {
  int totalAttributes = this->attributes.size();
  if (totalAttributes == 0) {
    //if no attributes, return nothing
    return NULL;
  }
  //loop through each attributes
  string result{"\t/*attributes*/"};
  for (int i = 0; i < totalAttributes; i++) {
    result += "\n\t";
    result += this->attributes[i].generateDeclaration();
  }
  return result;
}

//generate constructor
string ClassDescriptor::generateConstructor() {
  string result{"\t/*constructor*/\n"};
  int totalAttributes = this->attributes.size();
  //if no attributes
  if (totalAttributes == 0) {
    return result + "\tpublic " + this->name + "(){\n\t\t\n\t}";
  }
  result += "\tpublic " + this->name + "(";
  //if there is attributes
  int totalInConstructor = 0;
  for (int i = 0; i < totalAttributes; i++) {
    //and attributes must be in constructor
    if (this->attributes[i].getInConstructor()) {
      if (totalInConstructor != 0) {
        result += ", ";
      }
      totalInConstructor += 1;
      result += this->attributes[i].getType() + " " + this->attributes[i].getName();
    }
  }
  //if there is no attributes in constructor
  if (totalInConstructor == 0) {
    result += "){\n\t\t\n\t}";
    return result;
  }
  result += ") {";
  for (int i = 0; i < totalAttributes; i++) {
    if (this->attributes[i].getInConstructor()) {
      result += "\n\t\tthis." + this->attributes[i].getName() + " = " + this->attributes[i].getName() + ";";
    }
  }
  result += "\n\t}";
  return result;
}

//Generate getters
string ClassDescriptor::generateGetters() {
  int totalAttributes = this->attributes.size();
  if (totalAttributes == 0) {
    return "";
  }
  string result{};
  for (int i = 0; i < totalAttributes; i++) {
    string generatedGetter = this->attributes[i].generateGetter();
    if (generatedGetter != "") {
      result += "\n" + generatedGetter;
    }
  }
  return result;
}

//Generate setters
string ClassDescriptor::generateSetters() {
  int totalAttributes = this->attributes.size();
  if (totalAttributes == 0) {
    return "";
  }
  string result{};
  for (int i = 0; i < totalAttributes; i++) {
    string generatedSetter = this->attributes[i].generateSetter();
    if (generatedSetter != "") {
      result += "\n" + generatedSetter;
    }
  }
  return result;
}

//Generate .java class file
string ClassDescriptor::generate() {
  string fileContent{"/*comments*/\n"};
  //check if class is public
  if (this->publicClass) {
    fileContent += "public ";
  }
  //add class name
  fileContent += "class " + this->name + " {\n\n";
  //add every attributes declaration
  fileContent += this->generateAttributesStr();
  //add constructor if wanted
  fileContent += "\n\n";
  fileContent += this->generateConstructor();
  //add getters
  string getters = this->generateGetters();
  if (getters != "") {
    fileContent += "\n" + getters;
  }
  //add setters
  string setters = this->generateSetters();
  if (setters != "") {
    fileContent += "\n" + setters;
  }
  fileContent += "\n}";
  return fileContent;
}
