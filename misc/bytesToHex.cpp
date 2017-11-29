
std::string BytesToHex(
    const std::vector<unsigned char>& vecInput
    )
{
    // Convert to hex. Not using streams here for performance.
    std::string hexString( vecInput.size() * 2, ' ' );
    size_t pos = 0;
    const char* hexChars = "0123456789ABCDEF";
    for ( auto it = vecInput.begin(); it != vecInput.end(); ++it )
    {
        hexString[ pos ] = hexChars[ ( *it >> 4 ) & 0xF ];
        hexString[ pos + 1 ] = hexChars[ *it & 0xF ];
        pos += 2;
    }
    return hexString;
}
