#ifndef CLI_PARSER_H
#define CLI_PARSER_H
#include "option.h"
#include <string>
#include <vector>
using namespace std;

class CliParser {
private:
  bool enableArgs;
  vector<Option> options{};
  vector<string> arguments{};
  //trigger short option - no value
  bool triggerOption(char option);
  //trigger short option - value
  bool triggerOption(char option, string value);
  //trigger long option - no value
  bool triggerOption(string option);
  //trigger long option - value
  bool triggerOption(string option, string value);
  //is option registred ? return -1 if not
  int isOptionKnown(char option);
  //is option registred ? return -1 if not
  int isOptionKnown(string option);
  //invalid argument
  void invalid(string argument, int position);
  //invalid argument
  void invalid(char argument, int position);
  //check if there is one non-optional option
  bool checkNonOptional();

public:
  //constructor
  CliParser(bool enableArgs = false);
  //getter arguments
  vector<string>* getArguments();
  // add short option
  void addOption(char shortOption, bool optional, bool value);
  // add long option
  void addOption(string longOption, bool optional, bool value);
  // add short and long option
  void addOption(char shortOption, string longOption, bool optional, bool value);
  //parse arguments
  bool parse(int argc, char const *argv[]);
};

#endif
