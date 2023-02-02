#include <string>
#include <filesystem>
#include <sys/stat.h>
#include <iostream>
using namespace std;

int main(int argc, char const *argv[]) {
  if (stat("test", nullptr) == 0) {
    std::cout << "folder exist" << '\n';
  }
  std::cout << filesystem::current_path() << '\n';
  return 0;
}
