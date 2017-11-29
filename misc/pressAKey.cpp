// Mainly for Windows console apps which annoyingly disappear
// when you're running them in the debugger as soon as the
// program finishes, losing all output. An alternative to putting
// a breakpoint on main()'s closing brace :)
void PressAKey()
{
    #if (defined (_WIN32))
    if ( IsDebuggerPresent() )
    {
        std::cout << "\nPress ENTER: ";
        std::cin.ignore();
        std::endl( std::cout );
    }
    #endif
}
