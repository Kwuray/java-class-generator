#include "java-class/class-descriptor.h"
#include "java-class/attribute-descriptor.h"
#include "cli-parser/parser.hpp"
#include "cli-rules/cli-rules.h"
#include <iostream>
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
    clp.addOption('M', true, false);
    clp.addOption('m', true, false);
    clp.addOption('s', true, false);
    clp.addOption('e', true, false);
    clp.addOption("attr", true, true);
    clp.addOption('d', "destination-folder", true, true);
    if (clp.parse(argc, argv)) {
      javaClass->generate();
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
