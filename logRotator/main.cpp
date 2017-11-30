#include <boost/filesystem.hpp>

#include <iostream>
#include <fstream>

void RotateLogFiles( const boost::filesystem::path& dir )
{
    // We keep the last four logs; shuffle up any existing ones:
    boost::system::error_code ec;
    boost::filesystem::remove( dir / "foo.log.4", ec );
    for (unsigned int n = 3; n >=1; --n )
    {
        auto existingName = dir / ( "foo.log." + std::to_string(n) );
        auto newName = dir / ( "foo.log." + std::to_string( n + 1) );
        boost::filesystem::rename( existingName, newName, ec );
    }
    boost::filesystem::rename( dir / "foo.log", dir / "foo.log.1", ec );
}

int main()
{
    boost::filesystem::path p( "." );
    RotateLogFiles( p );
    std::ofstream ofs("./foo.log");
    if (ofs)
    {
        ofs << "Hello";
    }
    return 0;
}

