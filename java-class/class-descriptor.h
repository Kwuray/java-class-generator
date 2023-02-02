#ifndef CLASS_DESCRIPTOR_H
#define CLASS_DESCRIPTOR_H
#include "attribute-descriptor.h"
#include <string>
#include <vector>
using namespace std;

enum classNonAccessModifier {
  CLASS_FINAL,
  CLASS_ABSTRACT,
  CLASS_NONE
};

class ClassDescriptor {
private:
  string name{};
  bool publicClass;
  classNonAccessModifier nonAccessModifier;
  bool mainFunction;
  bool toStringFunction;
  string destpath{};
  vector<AttributeDescriptor> attributes{};
  //generate attributesContent
  string generateAttributesStr();
  //generate constructor
  string generateConstructor();
  //Generate getter
  string generateGetters();
  //Generate setter
  string generateSetters();
  //Generate main function
  string generateMain();
  //Generate toString function
  string generateToString();

public:
  //Constructeur
  ClassDescriptor(string name, bool publicClass, classNonAccessModifier nonAccessModifier);
  //setter main function
  void setMainFunction(bool mainFunction);
  //setter main function
  void setToStringFunction(bool toStringFunction);
  //getter name
  string getName();
  //getter nonaccess modifier
  string getClassNonAccessModifier();
  //Add attribute
  void addAttribute(attributeAccessModifier accessModifier, attributeNonAccessModifier nonAccessModifier, string type, string name, attributeAccessModifier getter, attributeAccessModifier setter, bool inConstructor);
  //generate .java class file
  void generate();
  //get non access modifier based on char
  static classNonAccessModifier calculateNonAccess(char c);
  //setter destpath
  bool setDestPath(string folderPath);
  //getter destpath
  string getDestPath();
};

#endif
