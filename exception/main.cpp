// example of the best way to define your own exceptions

#include <iostream>
#include <exception>

class FooException: public std::runtime_error
{
public:
    explicit FooException( const std::string& message )
    : std::runtime_error(message)
    {}
};


int main()
{
    try
    {
        throw FooException( "Crikey, dead serious!" );
    }
    catch( const std::exception& e )
    {
        std::cout << e.what() << std::endl;
    }
    return 0;
}
	
