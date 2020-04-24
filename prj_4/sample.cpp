#include <functional>
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <tuple>
#include <iterator>
#include <algorithm>
#include <random>
#include <forward_list>
#include <sstream>

using namespace std;

static void print(const vector<int> &v)
{
    copy(begin(v), end(v), ostream_iterator<int>{cout, ", "});
    cout << '\n';
}


template <typename T, typename ...Ts>
auto concat(T t, Ts ...ts)
{
    if constexpr (sizeof...(ts) > 0) {
        return [=](auto ...parameters) { return t(concat(ts...)(parameters...)); };
    } else  {
        return t;
    }
}



namespace std {
ostream& operator << (ostream &os, const pair<int, string> &p) {
    return os << "(" << p.first << ", " << p.second << ")";
}
}

namespace canftin_std {
template <class InputIt, class OutputIt>
OutputIt copy(InputIt first, InputIt last, OutputIt d_first) {
  while (first != last) {
    *d_first++ = *first++;
  }
  return d_first;
}


template <class InputIt, class Size, class OutputIt>
OutputIt copy_n(InputIt first, Size count, OutputIt result) {
  if (count > 0) {
    *result++ = *first;
    for (Size i = 1; i < count; ++i) {
      *result++ = *++first;
    }
  }
  return result;
}

template <class ForwardIt, class UnaryPredicate>
ForwardIt partition(ForwardIt first, ForwardIt last, UnaryPredicate p) {
  first = std::find_if_not(first, last, p);
  if (first == last) return first;

  for (ForwardIt i = std::next(first); i != last; ++i) {
    if (p(*i)) {
      std::iter_swap(i, first);
      ++first;
    }
  }
  return first;
}

template <class ForwardIt>
void quicksort(ForwardIt first, ForwardIt last)
{
  if(first == last) return;
  auto pivot = *std::next(first, std::distance(first,last)/2);
  ForwardIt middle1 = std::partition(first, last, 
                        [pivot](const auto& em){ return em < pivot; });
  ForwardIt middle2 = std::partition(middle1, last, 
                        [pivot](const auto& em){ return !(pivot < em); });
  quicksort(first, middle1);
  quicksort(middle2, last);
}

}

int main()
{
  /*
    auto twice  ([] (int i) { return i * 2; });
    auto thrice ([] (int i) { return i * 3; });

    auto combined (concat(twice, thrice, std::plus<int>{}));

    std::cout << combined(2, 3) << '\n';
  
  std::string in("1234567890");
  std::string out;

  canftin_std::copy_n(in.begin(), 4, std::back_inserter(out));
  std::cout << out << '\n';


  vector<pair<int, string>> v {
    {1, "one"}, {2, "two"}, {3, "three"}, {4, "four"}, {5, "five"}
  };

  map<int, string> m;

  copy_n(begin(v), 3, inserter(m, begin(m)));

  auto shell_it (ostream_iterator<pair<int, string>>{cout, ", "});
  copy(begin(m), end(m), shell_it);
  cout << '\n';

  

  vector<int> v {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  random_device rd;
  mt19937 g {rd()};

  cout << is_sorted(begin(v), end(v)) << '\n';

  shuffle(begin(v), end(v), g);

  cout << is_sorted(begin(v), end(v)) << '\n';
  print(v);

  sort(begin(v), end(v));

  cout << is_sorted(begin(v), end(v)) << '\n';
  print(v);

  shuffle(begin(v), end(v), g);

  print(v);

  partition(begin(v), end(v), [](int i) { return i < 5; });

  print(v);

  std::vector<int> v1 = {0,1,2,3,4,5,6,7,8,9};
  std::cout << "Original vector:\n    ";
  for (int elem : v1)
    std::cout << elem << ' ';

  auto it = std::partition(v1.begin(), v1.end(), [](int i){return i % 2 == 0;});

  std::cout << "\nPartitioned vector:\n    ";
  std::copy(std::begin(v1), it, std::ostream_iterator<int>(std::cout, " "));
  std::cout << " * ";
  std::copy(it, std::end(v1), std::ostream_iterator<int>(std::cout, " "));

  std::forward_list<int> fl = {1, 30, -4, 3, 5, -4, 1, 6, -8, 2, -5, 64, 1, 92};
  std::cout << "\nUnsorted list:\n    ";
  for (int n : fl)
    std::cout << n << ' ';
  std::cout << '\n';  

  canftin_std::quicksort(std::begin(fl), std::end(fl));
  std::cout << "Sorted using quicksort:\n    ";
  for(int fi : fl) std::cout << fi << ' ';
  std::cout << '\n';

*/

  vector<int> v {1, 2, 3, 4, 5};

  transform(begin(v), end(v), ostream_iterator<int>{cout, ", "},
            [] (int i) { return i * i; });
  cout << '\n';

  auto int_to_string ([](int i) {
      stringstream ss;
        ss << i;
        ss << "^2 = ";
        ss << i * i;
        return ss.str();
  });

  vector<string> vs;

  transform(begin(v), end(v), back_inserter(vs), int_to_string);

  copy(begin(vs), end(vs), ostream_iterator<string>{cout, "\n"});
}