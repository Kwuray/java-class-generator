#include "parser.hpp"
#include "option.hpp"
#include <string>
#include <vector>
#include <iostream>
using namespace std;

//constructor
CliParser::CliParser(bool enableArgs) {
  this->enableArgs = enableArgs;
}

//by default, trigger return false
//trigger short option - no value
inline bool CliParser::triggerOption(CliParser *parser, char option) {
  return false;
}

//trigger short option - value
inline bool CliParser::triggerOption(CliParser *parser, char option, string value) {
  return false;
}

//trigger long option - no value
inline bool CliParser::triggerOption(CliParser *parser, string option) {
  return false;
}

//trigger long option - value
inline bool CliParser::triggerOption(CliParser *parser, string option, string value) {
  return false;
}

//getter arguments
vector<string>* CliParser::getArguments() {
  return &this->arguments;
}

//add short option
void CliParser::addOption(char shortOption, bool optional, bool value) {
  this->options.push_back(Option(shortOption, optional, value));
}

//add long option
void CliParser::addOption(string longOption, bool optional, bool value) {
  this->options.push_back(Option(longOption, optional, value));
}

//add short and long option
void CliParser::addOption(char shortOption, string longOption, bool optional, bool value) {
  this->options.push_back(Option(shortOption, longOption, optional, value));
}

//is option registred ?
int CliParser::isOptionKnown(char option) {
  for (int i = 0; i < this->options.size(); i++) {
    if (this->options[i].getShortOption() == option) {
      return i;
    }
  }
  return -1;
}

//is option registred ?
int CliParser::isOptionKnown(string option) {
  for (int i = 0; i < this->options.size(); i++) {
    if (this->options[i].getLongOption() == option) {
      return i;
    }
  }
  return -1;
}

//invalid argument
void CliParser::invalid(string argument, int position) {
  std::cout << "Invalid argument : \"" << argument << "\" at position " << position  << '\n';
  if (this->hint != "") {
    //display hint
    std::cout << this->hint << '\n';
  }
}

//invalid argument
void CliParser::invalid(char argument, int position) {
  std::cout << "Invalid argument : \"" << argument << "\" at position " << position  << '\n';
  if (this->hint != "") {
    //display hint
    std::cout << this->hint << '\n';
  }
}

//check if there is one non-optional option
//return true if there is not no optional
bool CliParser::checkNonOptional() {
  for (int i = 0; i < options.size(); i++) {
    if (!options[i].getOptional()) {
      return false;
    }
  }
  return true;
}

//parse arguments
bool CliParser::parse(int argc, char const *argv[]) {
  /*!!!!!!!!!!!!!!!*/
  //convert into String vector
  vector<string> argvS{};
  for (int i = 1; i < argc; i++) {
    argvS.push_back(string{argv[i]});
  }
  //test all arg
  int argIndex = 0;
  int argOffset = 0;
  int valueOffset = 0;
  while (argIndex < argvS.size()) {
    int optionIndex = -1;
    int potentialArgValueIndex = argIndex + 1 + valueOffset;
    //if it's short option
    if (argvS[argIndex].size() >= 2 && argvS[argIndex][0] == '-' && argvS[argIndex][1] != '-') {
      char shortOption = argvS[argIndex][1 + argOffset];
      //is the option known ? ==> error if not
      optionIndex = this->isOptionKnown(shortOption);
      if (optionIndex == -1) {
        this->invalid(shortOption, argIndex + 1);
        return false;
      }
      //what is his type ?
      switch (this->options[optionIndex].getType()) {
        //short option no value
        case OPTION_SHORT:
        case OPTION_SHORT_LONG:
          if (!this->triggerOption(this, shortOption)) {
            this->invalid(shortOption, argIndex + 1);
            return false;
          }
          break;
        case OPTION_SHORT_VALUE:
        case OPTION_SHORT_LONG_VALUE:
          //we need to determine where is the value
          //we first check if there is an arg after
          //(next arg size > 2 and no "-" in front)
          if (potentialArgValueIndex < argvS.size() && (argvS[potentialArgValueIndex].size() > 2 && argvS[potentialArgValueIndex][0] != '-')) {
            string value = argvS[potentialArgValueIndex];
            //the value is the next arg, we are sure
            if (!this->triggerOption(this, shortOption, value)) {
              //trigger failed
              this->invalid(shortOption, argIndex + 1);
              return false;
            }
          } else {
            //the value should be after the flag
            if (argvS[argIndex].substr(2) == "") {
              this->setHint("Please provide a value.");
              this->invalid(argvS[argIndex][1], argIndex + 1);
              return false;
            }
            if (!this->triggerOption(this, argvS[argIndex][1], argvS[argIndex].substr(2))) {
              this->invalid(argvS[argIndex][1], argIndex + 1);
              return false;
            }
          }
          //incremente value offset
          valueOffset++;
          break;
        case OPTION_LONG_VALUE:
          break;
        case OPTION_LONG:
          break;
      }
        //we can incremente offset
        argOffset++;
        //if there is only "-", we can go to the next arg
        if (argvS[argIndex].size() - 1 == argOffset) {
          argIndex += valueOffset + 1;
          argOffset = 0;
          valueOffset = 0;
        }
    } else if (argvS[argIndex].size() > 2 && argvS[argIndex][0] == '-' && argvS[argIndex][1] == '-') {
      //if contain "=", it's long option with value
      int equalsIndex = argvS[argIndex].find("=");
      if (equalsIndex == -1) {
        //it's a long option, no value
        string option = argvS[argIndex].substr(2);
        //is the option known ? ==> error if not
        optionIndex = this->isOptionKnown(option);
        if (optionIndex == -1) {
          this->invalid(option, argIndex + 1);
          return false;
        }
        if (!this->triggerOption(this, option)) {
          this->invalid(option, argIndex + 1);
          return false;
        }
      } else {
        //long option with value
        string option = argvS[argIndex].substr(2, equalsIndex - 2);
        string value = argvS[argIndex].substr(equalsIndex + 1);
        //is the option known ? ==> error if not
        optionIndex = this->isOptionKnown(option);
        if (optionIndex == -1) {
          this->invalid(option, argIndex + 1);
          return false;
        }
        if (!this->triggerOption(this, option, value)) {
          this->invalid(option, argIndex + 1);
          return false;
        }
      }
      argIndex++;
    } else {
      //argument
      if (!this->enableArgs) {
        //argument invalid
        this->invalid(argvS[argIndex], argIndex + 1);
        return false;
      }
      this->arguments.push_back(argvS[argIndex]);
    }
    this->options[optionIndex].setOptional(true);
  }
  //check if non optional option were in args
  if (!this->checkNonOptional()) {
    std::cout << "Syntax error (non-optional params)" << '\n';
    return false;
  }
  return true;
}

//setter hint
void CliParser::setHint(string hint) {
  //yellow hint
  this->hint = "\x1B[33mhint : " + hint + "\x1B[0m";
}
