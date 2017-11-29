// Create a buffer with a dynamic size on the heap
// which will get deleted automatically when it
// goes out of scope. An alternative is to create
// a vector and accessing it via its data() function

size_t bufLen = 512;
std::unique_ptr<uint8_t[]> buf( new uint8_t[ bufLen ] );
