#include "list.hpp"
#include <numeric>
#include <algorithm>

auto main() ->int
{
  List_<int> n( 1, 2, 3, 4, 5, 6);
  n.push_back(44,33,22,44);
  n.push_front(-100, -190);
  n.print();
  List_<int> nums {std::move(n)};
  //
  std::cout << "\n- sum: ";
  auto sum = std::accumulate(nums.begin(), nums.end(), 0);
  std::cout << sum << '\n' << "- after sorting: ";
  nums.sort(false);
  nums.print();
  //
  std::cout << '\n' << "- show odd values using `for_each` loop: ";
  std::for_each(nums.begin(), nums.end(), [](auto i = 0) -> void {
    if ( (i & 1)  ) { std::cout << i << ' '; }
  });
}
