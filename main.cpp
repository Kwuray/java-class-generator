#include "class-descriptor.h"
#include "attribute-descriptor"
#include <iostream>
#include <fstream>

int main(int argc, char *argv[]) {
  ClassDescriptor c{"MaClasse", true, false};
  // Create and open a new Java file
  ofstream javaFile("filename.txt");
  // Write to the file
  javaFile << c.generate();
  // Close the file
  javaFile.close();
}
