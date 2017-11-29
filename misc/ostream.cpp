// To allow your type T to be printed, create a free function
// like this. You should put this function in the same namespace as your type.

std::ostream& operator<<( std::ostream& os, const T& value )
{
    os << convertMyTypeToString( value );
    return os;
}
