#include <string>
#include <iostream>
#include <variant>

using namespace std;

struct PrintVisitor
{
  void operator()(int i) { cout << "int: " << i << '\n'; }
  void operator()(float f) { cout << "float: " << f << '\n'; }
  void operator()(const string& s) { cout << "str: " << s << '\n'; }
};

int main() {
  variant<int, float, string> intFloatString;
  static_assert(variant_size_v<decltype(intFloatString)> == 3);

  visit(PrintVisitor{}, intFloatString);

  // index will show the currently used 'type'
  std::cout << "index = " << intFloatString.index() << std::endl;
  intFloatString = 100.0f;
  std::cout << "index = " << intFloatString.index() << std::endl;
  intFloatString = "hello super world";
  std::cout << "index = " << intFloatString.index() << std::endl;

  visit(PrintVisitor{}, intFloatString);

  // visit:
  std::visit(PrintVisitor{}, intFloatString);
  intFloatString = 10;
  std::visit(PrintVisitor{}, intFloatString);
  intFloatString = 10.0f;
  std::visit(PrintVisitor{}, intFloatString);
  intFloatString = "fejfoaeijf";
  std::visit(PrintVisitor{}, intFloatString);
  
}