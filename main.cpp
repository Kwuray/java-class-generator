#include "java-class/class-descriptor.h"
#include "java-class/attribute-descriptor.h"
#include "cli-parser/parser.h"
#include "cli-rules/cli-rules.h"
#include <iostream>
#include <fstream>
#include <regex>
using namespace std;

//global variable
ClassDescriptor *javaClass;

int main(int argc, char const *argv[]) {
  //global variable
  extern ClassDescriptor *javaClass;
  if (argc == 1) {
    cout << "Vous n'avez saisie aucun paramètre !" << '\n';
    return -1;
  }
  CliParser clp{true};
  clp.addOption('c', "class", true, true);
  if (!clp.parse(argc, argv)) {
    return -1;
  }
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
  delete javaClass;
  return 0;
}
