#include "class-descriptor.h"
#include "attribute-descriptor.h"
#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char *argv[]) {
  ClassDescriptor c{"MaClasse", false, false};
  c.addAttribute(ATTRIBUTE_ACCESS_PRIVATE, ATTRIBUTE_NONACCESS_SYNCHRONIZED, "int", "total", ATTRIBUTE_ACCESS_PRIVATE, ATTRIBUTE_ACCESS_PRIVATE, false);
  c.addAttribute(ATTRIBUTE_ACCESS_NONE, ATTRIBUTE_NONACCESS_TRANSIENT, "String", "x", ATTRIBUTE_ACCESS_NONE, ATTRIBUTE_ACCESS_PRIVATE, false);
  c.addAttribute(ATTRIBUTE_ACCESS_PROTECTED, ATTRIBUTE_NONACCESS_NONE, "double", "z", ATTRIBUTE_ACCESS_PRIVATE, ATTRIBUTE_ACCESS_NONE, true);
  // Create and open a new Java file
  ofstream javaFile(c.getName() + ".java");
  // Write to the file
  string javaFileContent = c.generate();
  javaFile << javaFileContent;
  // Close the file
  javaFile.close();
  std::cout << javaFileContent << "\n";
}
