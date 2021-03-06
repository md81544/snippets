#include "JsonParser.h"

namespace xyz
{

JsonParser::JsonParser( std::vector<uint8_t> vecJson )
    : m_validState( false )
{
    try
    {
        std::string json( vecJson.begin(), vecJson.end() );
        std::istringstream iss( json );
        boost::property_tree::read_json( iss, m_propertyTree );
        m_validState = true;
    }
    catch ( const std::exception& e )
    {
        // TODO log this
    }
    catch ( ... )
    {
        // TODO log this
    }
}

} // namespace xyz
