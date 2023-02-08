#include "attribute-descriptor.h"
#include <string>
#include <cctype>
//Constructeur
AttributeDescriptor::AttributeDescriptor(attributeAccessModifier accessModifier, attributeNonAccessModifier nonAccessModifier, string type, string name, attributeAccessModifier getter, attributeAccessModifier setter, bool inConstructor) {
  this->accessModifier = accessModifier;
  this->nonAccessModifier = nonAccessModifier;
  this->type = type;
  this->setName(name);
  this->getter = getter;
  this->setter = setter;
  this->inConstructor = inConstructor;
}


//getter accessModifier
string AttributeDescriptor::getAccessModifier(attributeAccessModifier *accessModifer) {
  switch (accessModifier) {
    case ATTRIBUTE_ACCESS_PUBLIC:
      return "public";
    case ATTRIBUTE_ACCESS_PRIVATE:
      return "private";
    case ATTRIBUTE_ACCESS_PROTECTED:
      return "protected";
    default:
      return "";
  }
}

//getter non-accessModifier
string AttributeDescriptor::getNonAccessModifier() {
  switch (this->nonAccessModifier) {
    case ATTRIBUTE_NONACCESS_FINAL:
      return "final";
    case ATTRIBUTE_NONACCESS_STATIC:
      return "static";
    case ATTRIBUTE_NONACCESS_ABSTRACT:
      return "abstract";
    case ATTRIBUTE_NONACCESS_TRANSIENT:
      return "transient";
    case ATTRIBUTE_NONACCESS_SYNCHRONIZED:
      return "synchronized";
    case ATTRIBUTE_NONACCESS_VOLATILE:
      return "volatile";
    default:
      return "";
  }
}

//getter type
string AttributeDescriptor::getType() {
  return this->type;
}

//getter name
string AttributeDescriptor::getName(bool upper) {
  if (upper) {
    return static_cast<char>(toupper(this->name[0])) + this->name.substr(1);
  }
  return this->name;
}

//setter name
void AttributeDescriptor::setName(string name) {
  this->name = name;
  this->setAttrType();
}

//setter type
void AttributeDescriptor::setAttrType() {
  this->attrType = isupper(this->getType()[0]) ? TYPE_OBJECT : TYPE_PRIMITIVE;
}

//getter signature attribute (type name)
string AttributeDescriptor::getSignature() {
  return this->getType() + " " + this->getName();
}

//generate Affectation
string AttributeDescriptor::getAffectation() {
  //if there is setter
  return this->setter == ATTRIBUTE_ACCESS_NONE ? "this." + this->getName() + " = " + this->getName() + ";" : "set" + this->getName(true) + "(" + this->getName() + ");";
}

//getter inConstructor
bool AttributeDescriptor::getInConstructor() {
  return this->inConstructor;
}

//Generate declaration (public/private/protected type var)
string AttributeDescriptor::generateDeclaration() {
  //add access modifier
  string result{this->getAccessModifier(&this->accessModifier)};
  //add space if needed
  result += this->getAccessModifier(&this->accessModifier) != "" ? " " : "";
  //add non access modifier
  result += this->getNonAccessModifier();
  //add space if needed
  result += this->getNonAccessModifier() != "" ? " " : "";
  //add type and name
  result += this->getSignature() + ";";
  return result;
}

//Generate getter
string AttributeDescriptor::generateGetter() {
  if (this->getter == ATTRIBUTE_ACCESS_NONE) {
    //don't generate getter !
    return "";
  }
  return "\t/*getter " + this->getName() + "*/\n\t" + this->getAccessModifier(&this->getter) + " " + this->getType() + " get" + this->getName(true) + "(){\n\t\treturn this." + this->getName() + ";\n\t}";
}

//Generate setter
string AttributeDescriptor::generateSetter() {
  if (this->setter == ATTRIBUTE_ACCESS_NONE) {
    //don't generate getter !
    return "";
  }
  return "\t/*setter " + this->getName() + "*/\n\t " + this->getAccessModifier(&this->setter) + " void set" + this->getName(true) + "(" + this->getSignature() + "){\n\t\tthis." + this->getName() + " = " + this->getName() + ";\n\t}";
}

//Generate comparison
string AttributeDescriptor::generateComparison() {
  switch (this->attrType) {
    case TYPE_PRIMITIVE:
      return "\t\tif (this." + this->getName() + " != other." + this->getName() + ") {\n\t\t\treturn false;\n\t\t}";
    case TYPE_OBJECT:
      return "\t\tif (this." + this->getName() + " == null) {\n\t\t\tif (other." + this->getName() + " != null) {\n\t\t\t\treturn false;\n\t\t\t}\n\t\t} else if (!this." + this->getName() + ".equals(other." + this->getName() + ")) {\n\t\t\treturn false;\n\t\t}";
  }
}

//get non access modifier based on char
attributeAccessModifier AttributeDescriptor::calculateAccess(char c) {
  switch (c) {
    case '+':
      return ATTRIBUTE_ACCESS_PUBLIC;
    case '-':
      return ATTRIBUTE_ACCESS_PRIVATE;
    case '~':
      return ATTRIBUTE_ACCESS_PROTECTED;
    case 'n':
      return ATTRIBUTE_ACCESS_NONE;
    default:
      return ATTRIBUTE_ACCESS_NONE;
  }
}

//get non access modifier based on char
attributeNonAccessModifier AttributeDescriptor::calculateNonAccess(char c) {
  switch (c) {
    case 'f':
      return ATTRIBUTE_NONACCESS_FINAL;
    case 's':
      return ATTRIBUTE_NONACCESS_STATIC;
    case 'a':
      return ATTRIBUTE_NONACCESS_ABSTRACT;
    case 't':
      return ATTRIBUTE_NONACCESS_TRANSIENT;
    case 'S':
      return ATTRIBUTE_NONACCESS_SYNCHRONIZED;
    case 'v':
      return ATTRIBUTE_NONACCESS_VOLATILE;
    case 'n':
      return ATTRIBUTE_NONACCESS_NONE;
    default:
      return ATTRIBUTE_NONACCESS_NONE;
  }
}
