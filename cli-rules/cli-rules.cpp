#include "cli-rules.h"
#include "../cli-parser/parser.h"
#include <string>
#include <regex>
#include <iostream>
using namespace std;

//trigger short option - value
bool CliParser::triggerOption(char option, string value) {
  switch (option) {
    case 'c':
      return CliRules::classObj(&value);
  }
  return false;
}

//trigger long option - value
bool CliParser::triggerOption(string option, string value) {
  if (option == "class") {
    return CliRules::classObj(&value);
  }
  return false;
}

//create java class obj
bool CliRules::classObj(string *value) {
  //global variable
  extern ClassDescriptor *javaClass;
  if (javaClass != nullptr) {
    //already define !
    return false;
  }
  regex pattern{"^(y|n{1})/(f|a|n{1})/([[:alpha:]]+)$"};
  smatch matchs;
  if (regex_match(*value, matchs, pattern)) {
    bool publicClass = matchs[1].str() == "y" ? true : false;
    classNonAccessModifier nonAccess = ClassDescriptor::calculateNonAccess(matchs[2].str()[0]);
    javaClass = new ClassDescriptor{matchs[3].str(), publicClass, nonAccess};
    return true;
  }
  return false;
}
