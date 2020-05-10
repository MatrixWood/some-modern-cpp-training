#include <iostream>
#include <string>
#include <tuple>

void f(std::string s) {
  std::cout << "Moved or copied: " << s << '\n';
}

void g(std::string&& s) {
  std::cout << "Moved " << s << '\n';
}

std::string h() {
  std::string s("test");
  return s;
}

struct A
{
	A() {};
	A(const A&) = delete;	// A objects cannot be copied
};

void f(const A&)
{
	std::cout << "lval, ";	// forwarded as lvalue reference
}

void f(A&&)
{
	std::cout << "rval, ";	// forwarded as rvalue reference
}

template <typename T> void good_fwd(T&& t) { f(std::forward<T>(t)); }
template <typename T> void bad_fwd(T&& t) { f(t); }
template <typename T> void ugly_fwd(T t) { f(t); }

int main() {
  std::string test("123");
  f(test);

  std::tuple t(1, 2, 0.3, std::string("4"));
}