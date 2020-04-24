#include <iostream>
#include <vector>
#include <boost/type_index.hpp>


using namespace std;
using boost::typeindex::type_id_with_cvr;

class Widget {

};

std::vector<Widget> createVec() {
  return vector<Widget>();
}

template <typename T>
void f(const T& param) {
  cout << "T = " << type_id_with_cvr<T>().pretty_name() << endl;
  cout << "param = " << type_id_with_cvr<decltype(param)>().pretty_name() << endl;
}

int main () {
  std::vector<Widget> vw;
  Widget w;

  const auto vw2 = createVec();
  f(&vw2[0]);
  f(w);
  f(vw);
  f(&w);
  f(&vw);
}