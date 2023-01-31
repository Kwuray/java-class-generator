#include "class-descriptor.h"
#include "attribute-descriptor.h"
#include "cli-parser/parser.h"
#include <iostream>
#include <fstream>
#include <regex>
using namespace std;

//global variable
ClassDescriptor *javaClass;

//trigger short option - value
bool CliParser::triggerOption(char option, string value) {
  switch (option) {
    case 'c':
      if (javaClass != nullptr) {
        //already define !
        return false;
      }
      regex pattern{"^(y|n){1}/(f|a){0,1}/([[:alpha:]])+$"};
      smatch matchs;
      if (regex_match(value, matchs, pattern)) {
        bool publicClass = matchs[0].str() == "y" ? true : false;
        classNonAccessModifier nonAccess = CLASS_NONE;
        if (matchs[1].str() == "f") {
          nonAccess = CLASS_FINAL;
        } else if (matchs[1].str() == "a") {
          nonAccess = CLASS_ABSTRACT;
        }
        javaClass = new ClassDescriptor{matchs[2].str(), publicClass, nonAccess};
        return true;
      }
      return false;
  }
  return false;
}

//trigger long option - value
bool CliParser::triggerOption(string option, string value) {
  if (option == "class") {
    if (javaClass != nullptr) {
      //already define !
      return false;
    }
    regex pattern{"^(y|n){1}/(f|a){0,1}/([[:alpha:]])+$"};
    smatch matchs;
    if (regex_match(value, matchs, pattern)) {
      bool publicClass = matchs[0].str() == "y" ? true : false;
      classNonAccessModifier nonAccess = CLASS_NONE;
      if (matchs[1].str() == "f") {
        nonAccess = CLASS_FINAL;
      } else if (matchs[1].str() == "a") {
        nonAccess = CLASS_ABSTRACT;
      }
      javaClass = new ClassDescriptor{matchs[2].str(), publicClass, nonAccess};
      return true;
    }
    return false;
  }
  return false;
}

int main(int argc, char const *argv[]) {
  CliParser clp{true};
  clp.addOption('c', "class", true, true);
  if (clp.parse(argc, argv)) {
    javaClass->setToStringFunction(true);
    javaClass->setMainFunction(true);
    //c.addAttribute(ATTRIBUTE_ACCESS_PRIVATE, ATTRIBUTE_NONACCESS_SYNCHRONIZED, "int", "total", ATTRIBUTE_ACCESS_NONE, ATTRIBUTE_ACCESS_PUBLIC, false);
    //c.addAttribute(ATTRIBUTE_ACCESS_NONE, ATTRIBUTE_NONACCESS_TRANSIENT, "String", "x", ATTRIBUTE_ACCESS_NONE, ATTRIBUTE_ACCESS_PRIVATE, false);
    //c.addAttribute(ATTRIBUTE_ACCESS_PROTECTED, ATTRIBUTE_NONACCESS_NONE, "double", "z", ATTRIBUTE_ACCESS_PRIVATE, ATTRIBUTE_ACCESS_NONE, true);
    // Create and open a new Java file
    ofstream javaFile(javaClass->getName() + ".java");
    // Write to the file
    string javaFileContent = javaClass->generate();
    javaFile << javaFileContent;
    // Close the file
    javaFile.close();
  }
  delete javaClass;

}
