#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// Obviously doing a hex dump in Linux is a piece of cake but
// there's no *native* way to do it simply in Windows so
// this is a quick & dirty solution.

void hexDump( const std::vector<uint8_t>& buf )
{
    unsigned char hexDigits[] = "0123456789abcdef";

    long lengthRemaining = buf.size();
    int index = 0;

    while ( lengthRemaining > 0 )
    {
        printf( "%8.8x  ", index );
        // print the hex
        for ( int i = 0; i < 16; ++i )
        {
            if ( i >= lengthRemaining )
            {
                printf( "   " );
                if ( i == 7 )
                {
                    printf( " " );
                }
            }
            else
            {
                printf( "%c", hexDigits[ buf[ index + i ] >> 4 ] );
                printf( "%c", hexDigits[ buf[ index + i ] & 0x0f ] );
                if ( i == 7 )
                {
                    printf( " " );
                }
                printf( " " );
            }
        }
        printf( "  |" );
        // print the characters
        for ( int i = 0; i < 16; ++i )
        {
            if ( i >= lengthRemaining )
            {
                printf( " " );
            }
            else
            {
                uint8_t c = buf[ index + i ];
                if ( c < 32 || c > 126 )
                {
                    printf( "." );
                }
                else
                {
                    printf( "%c", c );
                }
            }
        }
        printf( "|\n" );
        index += 16;
        lengthRemaining -= 16;
    }
}

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
        hexDump( vec );
    }
    catch ( const std::exception& e )
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
