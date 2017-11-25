#include <iostream>
#include <iomanip>

#include <time.h>

// This is an example of how to do high-res timing on Linux
// clang++ -std=c++14 -Wall -Wextra -pedantic -o t main.cpp
//
// Could be put into the HiResTimer class with #ifdefs ?

timespec diff( timespec start, timespec end )
{
    timespec temp;
    if ( ( end.tv_nsec - start.tv_nsec ) < 0 )
    {
        temp.tv_sec = end.tv_sec - start.tv_sec - 1;
        temp.tv_nsec = 1000000000 + end.tv_nsec - start.tv_nsec;
    }
    else
    {
        temp.tv_sec = end.tv_sec - start.tv_sec;
        temp.tv_nsec = end.tv_nsec - start.tv_nsec;
    }
    return temp;
}

int main()
{

    timespec time1;
    timespec time2;
    size_t temp{0};
    clock_gettime( CLOCK_PROCESS_CPUTIME_ID, &time1 );
    for ( size_t i = 0; i < 120000000; i++ )
    {
        temp += temp;
    }
    clock_gettime( CLOCK_PROCESS_CPUTIME_ID, &time2 );
    std::cout << diff( time1, time2 ).tv_sec << "."
              << std::setfill('0') << std::setw(9)
              << diff( time1, time2 ).tv_nsec << std::endl;


    return 0;
}

