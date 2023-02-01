#ifndef CLI_RULES_H
#define CLI_RULES_H
#include "../java-class/class-descriptor.h"
#include <string>
using namespace std;

class CliRules {
public:
  static bool classObj(string *value);

private:
  CliRules();
};

#endif
