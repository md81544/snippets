#include <iostream>
#include <string>
#ifdef __linux__
#include <typeinfo>
#endif


void PressAKey()
{
    std::cout << "\nPress ENTER ";
    std::cout.flush();
    std::cin.get();
}

#ifdef __linux
#define THROWUP( exception, message ) \
    throw exception( __FILE__, __LINE__, __func__, message )
#else
#define THROWUP( exception, message ) \
    throw exception( __FILE__, __LINE__, __FUNCSIG__, message )
#endif


class BaseException : public std::exception
{
public:
    BaseException(
        const char *exceptionFile,
        const unsigned int exceptionLine,
        const char *exceptionFunction,
        const std::string &message
        ) :
        fileName(exceptionFile),
        lineNumber(exceptionLine),
        functionSignature(exceptionFunction),
        details(message)
    {}
    virtual ~BaseException(){};

    virtual const char *what() const noexcept override
    {
        return details.c_str();
    }
    std::string file() const
    {
        return fileName;
    }
    std::string function() const
    {
        return functionSignature;
    }
    unsigned int line() const
    {
        return lineNumber;
    }

private:
    std::string  fileName;
    unsigned int lineNumber;
    std::string  functionSignature;
    std::string  details;
};

// Example sub-class
class DeadSeriousException : public BaseException
{
public:
    DeadSeriousException(
        const char *file,
        unsigned int line,
        const char *function,
        const std::string &message
        ) :
        BaseException(file, line, function, message) {}
};

int main()
{
    try
    {
        THROWUP(DeadSeriousException, "Crikey, dead serious!");
    }
    catch (const BaseException &ex)
    {
        std::string message = "Exception (" +
            std::string(typeid(ex).name()) +
            ") thrown in " +
            ex.file() + " +" +
            std::to_string(ex.line()) + " (" +
            ex.function() + "): " +
            ex.what();
        std::cout << message << std::endl;
    }

    PressAKey();
}
