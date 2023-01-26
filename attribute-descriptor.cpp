#include "attribute-descriptor.h"
#include <string>

//Constructeur
AttributeDescriptor::AttributeDescriptor(string name, AttributeAccessModifier accessModifier, bool write, bool read, attributeNonAccessModifier nonAccessModifier) {
  this->name = name;
  this->accessModifier = accessModifier;
  this->write = write;
  this->read = read;
  this-> = nonAccessModifier;
}
