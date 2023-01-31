#include "option.h"
#include <string>
using namespace std;

//constructor -- short option
Option::Option(char shortOption, bool optional, bool value) {
  this->shortOption = shortOption;
  this->setOptional(optional);
  this->type = value ? OPTION_SHORT_VALUE : OPTION_SHORT;
}

//constructor -- long option
Option::Option(string longOption, bool optional, bool value) {
  this->longOption = longOption;
  this->setOptional(optional);
  this->type = value ? OPTION_LONG_VALUE : OPTION_LONG;
}

//constructor -- short and long option
Option::Option(char shortOption, string longOption, bool optional, bool value) {
  this->shortOption = shortOption;
  this->longOption = longOption;
  this->setOptional(optional);
  this->type = value ? OPTION_SHORT_LONG_VALUE : OPTION_SHORT_LONG;
}

//getter type
optionType Option::getType() {
  return this->type;
}

//getter shortOption
char Option::getShortOption() {
  return this->shortOption;
}

//getter shortOption
string Option::getLongOption() {
  return this->longOption;
}

//setter optional
void Option::setOptional(bool value) {
  this->optional = value;
}

//setter optional
bool Option::getOptional() {
  return this->optional;
}
