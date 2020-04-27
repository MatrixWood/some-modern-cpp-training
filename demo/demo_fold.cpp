#include <iostream>
#include <type_traits>

using namespace std;


template <typename... Args>
void fold_print(Args&&... args) {
  (cout << ... << forward<Args>(args)) << '\n';
}

int main() {
  fold_print("hello", 10, 20, 30);
}