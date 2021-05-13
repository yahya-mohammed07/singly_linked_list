#include "list.hpp"
#include <numeric>
#include <algorithm>

auto main() ->int
{
  List_<int> n{3, 2, 6, 3, 90, 1, 0,  7};
  List_<int> nums {std::move(n)};
  nums.print();
  //
  std::cout << "\n- sum: ";
  auto sum = std::accumulate(nums.begin(), nums.end(), 0);
  std::cout << sum << '\n' << "- after sorting: ";
  nums.sort();
  nums.print();
  //
  std::cout << '\n' << "- show odd values using `for_each` loop: ";
  std::for_each(nums.begin(), nums.end(), [](auto i = 0) -> auto {
    if ( (i & 1)  ) { std::cout << i << ' '; }
  });
}
