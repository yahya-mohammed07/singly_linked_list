#include "list.hpp"

auto main() ->int
{
    List_<int> nums { 0, 1, 2, 3, 4, 5 };
    //
    std::cout << nums.size() << '\n';
    nums.pop_at(1);
    nums.print();
    //
    std::cin.get();
}
