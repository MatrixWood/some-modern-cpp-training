#include <iostream>
#include <memory>
using namespace std;

class Sample {
public:
  Sample() {
    cout << "Sample Constructor" << endl;
  }

  ~Sample() {
    cout << "Sample Destructor" << endl;
  }

  void publicFn() {
    cout << "This is public function of class." << endl;
  }
};

void TestUniquePtr_ReleaseMemory() {
  unique_ptr<Sample> up(new Sample{});
  up->publicFn();
  return;
}

int main() {
  TestUniquePtr_ReleaseMemory();
  return 0;
}