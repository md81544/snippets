#include <cstdint>
#include <iostream>
#include <iomanip>
#include <vector>
#include <iterator>
#include <fstream>

// Take a binary file (which is assumed to hold ONE number of arbitrary
// length) and reverses the order of the bytes (i.e. converts from little
// endian to big endian or vice versa). I'm surprised there's no easy
// way (that I can find) to do this via the linux command line. Maybe it's
// just me that needs it %)

void WriteFile(
    const std::vector<uint8_t>& vec,
    const std::string& filename
    )
{
    std::ofstream out( filename, std::ios::out | std::ios::binary );
    if ( !out )
    {
        throw std::runtime_error(
                "Could not open file " + filename + " for writing" );
    }
    std::copy(
        vec.begin(),
        vec.end(),
        std::ostream_iterator<uint8_t>( out )
        );
    out.close();
}

std::vector<uint8_t> ReadFile( const std::string& filename )
{
    std::ifstream in( filename, std::ios::in | std::ios::binary );
    if ( !in )
    {
        throw std::runtime_error(
            "Could not open file " + filename + " for reading" );
    }
    std::vector<uint8_t> vec;
    in.seekg( 0, std::ios_base::end );
    std::streampos fileSize = in.tellg();
    vec.resize( fileSize );

    in.seekg( 0, std::ios_base::beg );
    in.read( reinterpret_cast<char*>( &vec[ 0 ] ), fileSize );
    return vec;
}


int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cout << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }
    auto vecIn = ReadFile( argv[ 1 ] );
    std::vector<uint8_t> vecOut(vecIn.rbegin(), vecIn.rend());
    for ( uint8_t c : vecOut )
    {
        std::cout << std::hex << std::setw(2) << std::setfill('0')
            << static_cast<int>(c);
    }
    return 0;
}
