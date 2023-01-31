#ifndef OPTION_H
#define OPTION_H
#include <string>
using namespace std;

enum optionType {
  OPTION_SHORT,
  OPTION_SHORT_VALUE,
  OPTION_LONG,
  OPTION_LONG_VALUE,
  OPTION_SHORT_LONG,
  OPTION_SHORT_LONG_VALUE
};

class Option {
private:
  char shortOption;
  string longOption{};
  bool optional; //if not, when the option is in the arguments, it become true
  optionType type;

public:
  //constructor -- short option
  Option(char shortOption, bool optional, bool value);
  //constructor -- long option
  Option(string longOption, bool optional, bool value);
  //constructor -- short and long option
  Option(char shortOption, string description, bool optional, bool value);
  //getter type
  optionType getType();
  //getter shortOption
  char getShortOption();
  //getter longOption
  string getLongOption();
  //setter optional
  void setOptional(bool value);
  //setter optional
  bool getOptional();
};

#endif
