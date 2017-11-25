#pragma once

// Intended to be a *bit* compatible with the Boost timer interface.
// Does not support resume().
// Windows only.
// See chrono.cpp for a more portable solution.

#define WIN32_LEAN_AND_MEAN
#include "windows.h"

#include <iostream>
#include <string>

class HiResTimer
{
public:
    HiResTimer(const std::string& message = "")
        :
        m_WasStarted( false ),
        m_WasStopped( false ),
        m_Message( message )
    {
        start();
    }
    ~HiResTimer()
    {
        // Does nothing in dtor - call stop & format explicitly
    }

    void start()
    {
        if ( ::QueryPerformanceFrequency( &m_Frequency ) == FALSE )
        {
            throw std::runtime_error( "QueryPerformanceFrequency() failed" );
        }
        if ( ::QueryPerformanceCounter( &m_Started ) == FALSE )
        {
            throw std::runtime_error( "QueryPerformanceCounter() failed" );
        }
        m_WasStarted = true;
    }

    void stop()
    {
        m_WasStopped = true;
        ::QueryPerformanceCounter( &m_Stopped );
    }

    void format()
    {
        if ( !m_WasStarted )
        {
            return;
        }
        if ( !m_WasStopped )
        {
            stop();
        }
        double time =
            static_cast<double>( m_Stopped.QuadPart - m_Started.QuadPart ) /
            m_Frequency.QuadPart;
        time *= 1000; // convert to ms
        if ( !m_Message.empty() )
        {
            std::cout << m_Message << " - ";
        }
        std::cout << "Time taken: " << time << " millisecs\n";
    }

private:
    bool m_WasStarted;
    bool m_WasStopped;
    std::string m_Message;
    LARGE_INTEGER m_Frequency;
    LARGE_INTEGER m_Started;
    LARGE_INTEGER m_Stopped;
};


