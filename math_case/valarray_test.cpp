#include <iostream>
#include <valarray>

using namespace std;

int main() {
  valarray<int> ints1(7);
  valarray doubles = { 1.1, 2.2, 3.3 };
  for (auto i : doubles)
    cout << i << "\t";
  cout << "\n";
}