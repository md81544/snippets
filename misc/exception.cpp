// If you derive from std::runtime_error you do not need to define your own
// member to store the string. This is done for you in the std::exception (the
// base of std::runtime_error). It is not defined how the exception stores the
// string but it it should always work.

#include <stdexcept>
#include <string>

class MyException: public std::runtime_error
{
public:
    MyException( const std::string& message )
    : std::runtime_error( message )
    {}
};
