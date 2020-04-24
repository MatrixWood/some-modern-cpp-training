// clang++ -std=c++17 -fsanitize=address -fsanitize=undefined checked_iterator.cpp -o main
// g++ -std=c++17 checked_iterator.cpp -D_GLIBCXX_DEBUG -o main
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    vector<int> v {1, 2, 3};
    v.shrink_to_fit();

    const auto it (begin(v));

    cout << *it << endl;

    v.push_back(123);

    // Detected by GLIBC++ debug mode
    // or with llvm with activated -fsanitize=address -fsanitize=undefined
    cout << *it << endl;
}