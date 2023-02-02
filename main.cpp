#include "java-class/class-descriptor.h"
#include "java-class/attribute-descriptor.h"
#include "cli-parser/parser.hpp"
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
  //Parse cli arguments
  try {
    CliParser clp{true};
    clp.addOption('c', "class", true, true);
    clp.addOption("attr", true, true);
    if (clp.parse(argc, argv)) {
      javaClass->setToStringFunction(true);
      javaClass->setMainFunction(true);
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
    delete javaClass;
    return -1;
  } catch (...) {
    std::cout << "Unknown error occured" << '\n';
    delete javaClass;
    return -1;
  }
}
