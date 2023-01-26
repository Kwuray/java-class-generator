#ifndef ATTRIBUTE_DESCRIPTOR_H
#define ATTRIBUTE_DESCRIPTOR_H
#include <string>

enum attributeAccessModifier {
  PUBLIC,
  PRIVATE,
  PROTECTED,
  NONE
};

enum attributeNonAccessModifier {
  FINAL,
  STATIC,
  ABSTRACT,
  TRANSIENT,
  SYNCHRONIZED,
  VOLATILE,
  NONE
};

class AttributeDescriptor {
private:
  string name{};
  AttributeAccessModifier accessModifier;
  bool write;
  bool read;
  attributeNonAccessModifier nonAccessModifier;

public:
  //Constructeur
  AttributeDescriptor(string name, AttributeAccessModifier accessModifier, bool write, bool read, attributeNonAccessModifier nonAccessModifier);
};

#endif
