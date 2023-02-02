#include <string>
#include <regex>
#include <iostream>
using namespace std;

int main(int argc, char const *argv[]) {
  string s{"-/n/int/age/+/+;-/n/String/name/+/+"};
  regex pat{R"(\s*;\s*)"};
  sregex_token_iterator end{};
  for (sregex_token_iterator p{s.begin(), s.end(), pat, -1}; p!=end; ++p) {
    cout << p->str() << '\n';
  }
  return 0;
}
