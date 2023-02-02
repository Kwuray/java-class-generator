#include "cli-rules.h"
#include "../cli-parser/parser.hpp"
#include "../java-class/class-descriptor.h"
#include "../java-class/attribute-descriptor.h"
#include <string>
#include <regex>
#include <iostream>
using namespace std;

//trigger short option - value
bool CliParser::triggerOption(CliParser *parser, char option, string value) {
  switch (option) {
    case 'c':
      return CliRules::classObj(parser, &value);
    default:
      return false;
  }
}

//trigger long option - value
bool CliParser::triggerOption(CliParser *parser, string option, string value) {
  if (option == "class") {
    return CliRules::classObj(parser, &value);
  }

  if (option == "attr") {
    return CliRules::attrObj(parser, &value);
  }
  return false;
}

//create java class obj
bool CliRules::classObj(CliParser *parser, string *value) {
  //global variable
  extern ClassDescriptor *javaClass;
  if (javaClass != nullptr) {
    //already define !
    return false;
  }
  regex pattern{"^(y|n{1})/(f|a|n{1})/([[:alpha:]]+)$"};
  smatch matchs;
  if (regex_match(*value, matchs, pattern)) {
    //Set parameters
    bool publicClass = matchs[1].str() == "y" ? true : false;
    classNonAccessModifier nonAccess = ClassDescriptor::calculateNonAccess(matchs[2].str()[0]);
    //Create class
    javaClass = new ClassDescriptor{matchs[3].str(), publicClass, nonAccess};
    return true;
  }
  return false;
}

//create java attribute obj
bool CliRules::attrObj(CliParser *parser, string *value) {
  //global variable
  extern ClassDescriptor *javaClass;
  if (javaClass == nullptr) {
    //cannot create attribute !
    parser->setHint("First use -c or --class");
    return false;
  }
  regex pattern{"^(\\x2B|-|~|n{1})/(f|s|a|t|S|v|n{1})/([[:alpha:]]+)/([[:alpha:]]+)/(\\x2B|-|~|n{1})/(\\x2B|-|~|n{1})/(y|n{1})$"};
  smatch matchs;
  if (regex_match(*value, matchs, pattern)) {
    //Set parameters
    attributeAccessModifier attrAccess = AttributeDescriptor::calculateAccess(matchs[1].str()[0]);
    attributeNonAccessModifier attrNonAccess = AttributeDescriptor::calculateNonAccess(matchs[2].str()[0]);
    attributeAccessModifier getterAccess = AttributeDescriptor::calculateAccess(matchs[5].str()[0]);
    attributeAccessModifier setterAccess = AttributeDescriptor::calculateAccess(matchs[6].str()[0]);
    bool inConstructor = matchs[7].str() == "y" ? true : false;
    //add attribute
    javaClass->addAttribute(attrAccess, attrNonAccess, matchs[3], matchs[4], getterAccess, setterAccess, inConstructor);
    return true;
  }
  parser->setHint("value do not match pattern. please see man.");
  return false;
}
