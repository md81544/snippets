#include <iostream>
#include <random>

int main()
{
    std::random_device rd;
    std::mt19937 gen( rd() );
    // Range is inclusive, so we should see 0 and 255
    // in the output eventually
    std::uniform_int_distribution<> dis( 0, 255 );

    for ( int n = 0; n < 1000; ++n )
    {
        std::cout << dis( gen ) << ' ';
    }
    std::cout << '\n';
    return 0;
}
