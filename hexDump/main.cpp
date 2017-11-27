#include <cstdint>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

// Obviously doing a hex dump in Linux is a piece of cake but
// there's no *native* way to do it simply in Windows so
// this is a quick & dirty solution. Does not do paging or
// display of characters.

std::vector<uint8_t> ReadFile( const std::string& filename )
{
    std::ifstream in( filename, std::ios::in | std::ios::binary );
    if ( !in )
    {
        throw std::runtime_error(
            "Could not open file " + filename + " for reading" );
    }
    in.seekg( 0, std::ios_base::end );
    std::streampos fileSize = in.tellg();
    std::vector<uint8_t> vec( static_cast<size_t>( fileSize ) );
    in.seekg( 0, std::ios_base::beg );
    in.read( reinterpret_cast<char*>( vec.data() ), fileSize );
    return vec;
}

int main( int argc, char* argv[] )
{
    if ( argc < 2 )
    {
        std::cerr << "Usage " << argv[ 0 ] << " <filename>\n";
        return 2;
    }
    std::string fileName( argv[ 1 ] );
    try
    {
        auto vec = ReadFile( fileName );
        unsigned int count = 0;
        for ( auto it = vec.begin(); it != vec.end(); ++it )
        {
            std::cout << std::hex << std::setw( 2 ) << std::setfill( '0' )
                      << std::uppercase
                      << static_cast<unsigned int>( *it ) << " ";
            if ( ++count == 16 )
            {
                std::cout << "\n";
                count = 0;
            }
        }
    }
    catch ( const std::exception& e )
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}

