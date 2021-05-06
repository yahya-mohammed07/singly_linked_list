#include "list.hpp"
#include <numeric>
#include <algorithm>

auto main() ->int
{
  List_<int> nums{3, 2, 6, -1, 3, 90, 1, 0};
  //
  auto sum = std::accumulate(nums.begin(), nums.end(), 0);
  std::cout << sum << '\n';
  for ( const auto& i : nums) { // not including head // @fixme
    std::cout << i << ' ';
  }
  List_<int> temp;
  std::iota(temp.begin(), temp.end(), 10);
}
