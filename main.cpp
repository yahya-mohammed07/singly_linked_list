#include "list.hpp"

auto main() ->int
{
    List_<int> test;
    //
    test.push_back( 0 );
    test.push_back( 1 );
    test.push_back( 2 );
    test.push_back( 3 );
    test.push_back( 4 );
    test.push_back( 5 );
    //
    std::cout << test.size() << '\n';
    test.pop_at( 3 );
    test.print();
    //
    std::cin.get();
}
