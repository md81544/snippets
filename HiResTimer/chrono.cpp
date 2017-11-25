// This is an example using std::chrono
// Note VS2010 doesn't have chrono.
// Also note VS2012 cheats by typedef'ing high_resolution_clock to system_clock.
// Sadly, this means it has low precision (around 1ms)
// Works fine in VS2015. Not sure about VS2013.
// Works fine in Linux with g++ and clang++.

#include <iostream>
#include <chrono>

class Timer
{
public:
    Timer( std::string name )
        : m_TimerName( name ),
        m_Start( std::chrono::high_resolution_clock::now() )
    {}

    ~Timer()
    {
        if ( !m_StartedManually )
        {
            End();
        }
    }

    void Start()
    {
        m_StartedManually = true;
        m_Start = std::chrono::high_resolution_clock::now();
    }

    void End()
    {
        auto end = std::chrono::high_resolution_clock::now();
        auto micros = std::chrono::duration_cast<std::chrono::nanoseconds>(
            end - m_Start).count();
        std::cout << m_TimerName << ": time taken: " << micros << " nanoseconds."
            << std::endl;
    }

private:
    bool m_StartedManually{ false };
    std::string m_TimerName;
    std::chrono::high_resolution_clock::time_point m_Start;
};

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


int main()
{
    {
        Timer timer( "Doing stuff" );
        // We're timing a single cout:
        std::cout << "The cat sat on the mat\n";
    }
    PressAKey();
    return 0;
}

