class Foo
{
public:
    Foo();                          // ctor
    Foo( const Foo&  );             // copy ctor
    Foo( const Foo&& );             // move ctor
    Foo& operator=( const Foo& );   // assignment operator
    Foo& operator=( Foo&& );        // move assignment operator
};

