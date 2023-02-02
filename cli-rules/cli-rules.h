#ifndef CLI_RULES_H
#define CLI_RULES_H
#include "../cli-parser/parser.hpp"
#include <string>
using namespace std;

class CliRules {
public:
  //create java class obj
  static bool classObj(CliParser *parser, string *value);
  //create java attribute obj
  static bool attrObj(CliParser *parser, string *value);

private:
  CliRules();
};

#endif
