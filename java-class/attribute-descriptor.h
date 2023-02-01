#ifndef ATTRIBUTE_DESCRIPTOR_H
#define ATTRIBUTE_DESCRIPTOR_H
#include <string>
using namespace std;

enum attributeAccessModifier {
  ATTRIBUTE_ACCESS_NONE,
  ATTRIBUTE_ACCESS_PUBLIC,
  ATTRIBUTE_ACCESS_PRIVATE,
  ATTRIBUTE_ACCESS_PROTECTED,
};

enum attributeNonAccessModifier {
  ATTRIBUTE_NONACCESS_NONE,
  ATTRIBUTE_NONACCESS_FINAL,
  ATTRIBUTE_NONACCESS_STATIC,
  ATTRIBUTE_NONACCESS_ABSTRACT,
  ATTRIBUTE_NONACCESS_TRANSIENT,
  ATTRIBUTE_NONACCESS_SYNCHRONIZED,
  ATTRIBUTE_NONACCESS_VOLATILE,
};

class AttributeDescriptor {
private:
  attributeAccessModifier accessModifier;
  attributeNonAccessModifier nonAccessModifier;
  string type{};
  string name{};
  attributeAccessModifier getter;
  attributeAccessModifier setter;
  bool inConstructor;

public:
  //complete constructor
  AttributeDescriptor(attributeAccessModifier accessModifier, attributeNonAccessModifier nonAccessModifier, string type, string name, attributeAccessModifier getter, attributeAccessModifier setter, bool inConstructor);
  //getter accessModifier
  string getAccessModifier(attributeAccessModifier *accessModifer);
  //getter non-accessModifier
  string getNonAccessModifier();
  //getter inConstructor
  bool getInConstructor();
  //getter type
  string getType();
  //getter name
  string getName(bool upper = false);
  //get signature attribute (type name)
  string getSignature();
  //get affectation
  string getAffectation();
  //Generate declaration (public/private/protected type var)
  string generateDeclaration();
  //Generate getter
  string generateGetter();
  //Generate setter
  string generateSetter();
};

#endif
