#pragma once

#include "boost/property_tree/ptree.hpp"
#pragma warning( push )
#pragma warning( disable: 4715 ) // not all control paths return a value
#pragma warning( disable: 4512 ) // assignment operator could not be generated
#include "boost/property_tree/json_parser.hpp"
#pragma warning( pop )

#include <cstdint>
#include <string>
#include <vector>

namespace xyz
{

class JsonParser
{
public:
    explicit JsonParser(
        std::vector<uint8_t> vecJson
    );

    template<typename T>
    T Get( const std::string& key ) const
    {
        if ( ! m_validState )
        {
            return T();
        }
        try
        {
            return m_propertyTree.get<T>( key );
        }
        catch ( const std::exception& e )
        {
            // TODO log this?
            return T();
        }
        catch ( ... )
        {
            // TODO log this?  "Unknown exception encountered";
            return T();
        }
    }
private:
    bool m_validState;
    boost::property_tree::ptree m_propertyTree;
};

} // namespace xyz
