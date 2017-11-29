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
