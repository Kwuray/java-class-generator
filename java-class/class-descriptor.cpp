#include "class-descriptor.h"
#include "attribute-descriptor.h"
#include <string>
#include <vector>
using namespace std;
using namespace std;

//Constructeur
ClassDescriptor::ClassDescriptor(string name, bool publicClass, classNonAccessModifier nonAccessModifier) {
  this->name = name;
  this->publicClass = publicClass;
  this->nonAccessModifier = nonAccessModifier;
  this->mainFunction = false;
  this->toStringFunction = false;
}

//setter main function
void ClassDescriptor::setMainFunction(bool mainFunction) {
  this->mainFunction = mainFunction;
}

//setter main function
void ClassDescriptor::setToStringFunction(bool toStringFunction) {
  this->toStringFunction = toStringFunction;
}

//getter name
string ClassDescriptor::getName() {
  return this->name;
}

//getter nonaccess modifier
string ClassDescriptor::getClassNonAccessModifier() {
  switch (this->nonAccessModifier) {
    case CLASS_FINAL:
      return "final";
    case CLASS_ABSTRACT:
      return "abstract";
    case CLASS_NONE:
      return "";
    default:
      return "";
  }
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
    return "";
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
      result += this->attributes[i].getSignature();
    }
  }
  //if there is no attributes in constructor
  if (totalInConstructor == 0) {
    result += "){\n\t\t\n\t}";
    return result;
  }
  result += ") {";
  //attributes affectation
  for (int i = 0; i < totalAttributes; i++) {
    if (this->attributes[i].getInConstructor()) {
      result += "\n\t\t" + this->attributes[i].getAffectation();
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

//Generate main function
string ClassDescriptor::generateMain() {
  return "\t/*main function*/\n\tpublic static void main(String[] args){\n\t\t\n\t}";
}

//Generate toString function
string ClassDescriptor::generateToString() {
  return "\t/*to string function*/\n\tpublic String toString(){\n\t\treturn \"\";\n\t}";
}

//Generate .java class file
string ClassDescriptor::generate() {
  string fileContent{"/*comments*/\n"};
  //check if class is public
  fileContent += this->publicClass ? "public " : "";
  //add nonaccess modifier
  string nonAccessModifier = this->getClassNonAccessModifier();
  fileContent += nonAccessModifier != "" ? nonAccessModifier + " " : "";
  //add class name
  fileContent += "class " + this->name + " {\n\n";
  //add every attributes declaration
  string attributes = this->generateAttributesStr();
  fileContent += attributes != "" ? attributes + "\n\n" : "";
  //add constructor
  fileContent += this->generateConstructor();
  //add getters
  string getters = this->generateGetters();
  fileContent += getters != "" ? "\n" + getters : "";
  //add setters
  string setters = this->generateSetters();
  fileContent += setters != "" ? "\n" + setters : "";
  //add main function
  fileContent += this->mainFunction ? "\n\n" + this->generateMain() : "";
  fileContent += this->toStringFunction ? "\n\n" + this->generateToString() : "";
  fileContent += "\n}";
  return fileContent;
}

//get non access modifier based on char
classNonAccessModifier ClassDescriptor::calculateNonAccess(char c) {
  switch (c) {
    case 'f':
      return CLASS_FINAL;
    case 'a':
      return CLASS_ABSTRACT;
    case 'n':
      return CLASS_NONE;
    default:
      return CLASS_NONE;
  }
}
