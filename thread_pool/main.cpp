#include "boost/thread.hpp"

#ifdef _WIN32
// io_service.hpp on Windows complains if this isn't defined:
#define _WIN32_WINNT 0x0501
#endif

#include "boost/asio.hpp"

#include <chrono>
#include <iostream>
#include <random>

void PressAKey()
{
    std::cout << "\nPress ENTER ";
    std::cout.flush();
    std::cin.get();
}

boost::mutex g_mtx;

void Callback( const std::string &msg )
{
    // As this is on a separate thread we'd want to ensure no
    // exceptions escape from this function
    auto seed =
        std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::mt19937 rnd( static_cast<unsigned int>( seed ) );
    size_t waitFor = 1000 + rnd() % 2000;
    {
        boost::lock_guard<boost::mutex> lock( g_mtx );
        std::cout << std::setw( 5 ) << boost::this_thread::get_id() << ": "
                  << msg << std::endl;
    }
    boost::this_thread::sleep_for( boost::chrono::milliseconds( waitFor ) );
    {
        boost::lock_guard<boost::mutex> lock( g_mtx );
        std::cout << std::setw( 5 ) << boost::this_thread::get_id()
                  << ": (finished)" << std::endl;
    }
}

int main()
{
    // An example which abstracts away the (Windows) I/O completion
    // port way of working - we can pass arbitrary commands and parameters
    // into the queue and any number of threads can be sitting there ready
    // to pick up a piece of work. Underneath, Boost does use an IOCP on
    // Windows and epoll() on Linux.

    boost::asio::io_service ioService;
    boost::thread_group threadpool;

    try
    {
        {
            // Using a work object ensures that the worker threads
            // don't quit as soon as there are no available tasks in the 
            // queue. Only when the work object goes out of scope will
            // the worker threads then finish.
            boost::asio::io_service::work work( ioService );

            for ( int n = 0; n < 4; ++n )
            {
                // Create our worker threads
                threadpool.create_thread( [&ioService]() { ioService.run(); } );
            }

            // Now we can post work to the thread pool:
            ioService.post( boost::bind( Callback, "Hello World!" ) );
            ioService.post( boost::bind( Callback, "All your base" ) );
            ioService.post( boost::bind( Callback, "Are belong to us" ) );
            ioService.post(
                boost::bind( Callback, "You have no chance to survive" ) );
            ioService.post( boost::bind( Callback, "Make your time" ) );
            ioService.post( boost::bind( Callback, "For great justice" ) );
            ioService.post( boost::bind( Callback, "Roses are #F00" ) );
            ioService.post( boost::bind( Callback, "Violets are #00F" ) );
            ioService.post( boost::bind( Callback, "All of my base" ) );
            ioService.post( boost::bind( Callback, "Are belong to you" ) );
            // Avoiding use of bind:
            ioService.post(
                []() { Callback( "This one came via a lambda" ); } );
        } // work goes out of scope here
    }
    catch ( const std::exception &ex )
    {
        std::cout << ex.what() << std::endl;
    }

    // In theory we could do an ioService.stop() here to stop the queue of work.
    // In Windows this allows the queue to drain; under Linux (inc. Cygwin) the
    // queue doesn't drain and all untaken queue items are discarded. This
    // appears to be a function of the underlying mechanisms and for
    // performance. However destroying the work object works as expected on both
    // platforms, allowing the queue to drain first.
    // You might want to do a threadpool.interrupt_all() (don't forget to define
    // interruption points in the thread code) but otherwise the threads will
    // just run to completion eventually.
    threadpool.join_all();

    PressAKey();

    return 0;
}
