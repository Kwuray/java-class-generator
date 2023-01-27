#include "attribute-descriptor.h"
#include <string>

//Constructeur
AttributeDescriptor::AttributeDescriptor(attributeAccessModifier accessModifier, attributeNonAccessModifier nonAccessModifier, string type, string name, attributeAccessModifier getter, attributeAccessModifier setter, bool inConstructor) {
  this->accessModifier = accessModifier;
  this->nonAccessModifier = nonAccessModifier;
  this->type = type;
  this->name = name;
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

//getter inConstructor
bool AttributeDescriptor::getInConstructor() {
  return this->inConstructor;
}

//Generate declaration (public/private/protected type var)
string AttributeDescriptor::generateDeclaration() {
  return this->getAccessModifier(&this->accessModifier) + " " + this->getNonAccessModifier() + " " + this->getType() + " " + this->getName() + ";";
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
  if (this->getter == ATTRIBUTE_ACCESS_NONE) {
    //don't generate getter !
    return "";
  }
  return "\t/*setter " + this->getName() + "*/\n\t" + this->getAccessModifier(&this->setter) + " " + this->getType() + " set" + this->getName(true) + "(){\n\t\tthis." + this->getName() + " = " + this->getName() + ";\n\t}";
}
