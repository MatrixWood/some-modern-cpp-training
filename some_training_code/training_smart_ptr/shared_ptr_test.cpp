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

void TestSharedPtr_ReleaseMemory() {
  shared_ptr<Sample> sp(new Sample{});
  sp->publicFn();
  return;
}

shared_ptr<Sample> AFunc() {
  cout << "Enter AFunc" << endl;
  shared_ptr<Sample> sp(new Sample{});
  cout << "Exit AFunc" << endl;
  return sp;
}

void TestSharedPtr_ReferenceCount() {
  cout << "Enter TestSharedPtr_ReferenceCount" << endl;
  shared_ptr<Sample> retSp = AFunc();
  cout << "Exit TestSharedPtr_ReferenceCount" << endl;
  return;
}

void TestSharedPtr_ReferenceCount_Assignments() {
  cout << "Enter TestSharedPtr_ReferenceCount_Assignments" << endl;
  AFunc();
  cout << "Exit TestSharedPtr_ReferenceCount_Assignments" << endl;
  return;
}

void TestSharedPtr_MakeShared() {
  shared_ptr<Sample> sp = make_shared<Sample>();
  return;
}

int main() {
  TestSharedPtr_ReleaseMemory();
  cout << "------------------------------------------------" << endl;
  TestSharedPtr_ReferenceCount();
  cout << "------------------------------------------------" << endl;
  TestSharedPtr_ReferenceCount_Assignments();
  cout << "------------------------------------------------" << endl;
  TestSharedPtr_MakeShared();
  return 0;
}