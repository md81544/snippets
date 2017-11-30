void WriteFile(
    const std::vector<BYTE>& vec,
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
        std::ostream_iterator<BYTE>( out )
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
    in.seekg( 0, std::ios_base::end );
    std::streampos fileSize = in.tellg();
    std::vector<uint8_t> vec( fileSize );

    in.seekg( 0, std::ios_base::beg );
    in.read( reinterpret_cast<char*>( &vec[ 0 ] ), fileSize );
    return vec;
}

