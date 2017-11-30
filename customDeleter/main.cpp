#if (defined (_WIN32))
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#include <iostream>
#include <vector>
#include <string>
#include <memory>

auto PressAKey() -> void
{
#if (defined (_WIN32))
    if ( IsDebuggerPresent() )
    {
        std::cout << "\nPress ENTER: ";
        std::cin.ignore();
        std::endl( std::cout );
    }
#endif
}

class Foo
{
public:
    Foo()  { std::cout << "ctor\n"; };
    ~Foo() { std::cout << "dtor\n"; };
};


auto main() -> int
{
    {
        auto dt = []( Foo *f ) {
            delete f;
            std::cout << "Deleter called\n";
        };
        std::unique_ptr<Foo, decltype(dt)> p( new Foo, dt );
    }

    PressAKey();
    return 0;
}
