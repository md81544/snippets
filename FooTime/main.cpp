#include "boost/date_time/posix_time/posix_time.hpp"


namespace FooTime
{
    class Time
    {
    public:
        Time(const std::string &dateTimeString)
        {
            using boost::posix_time::time_input_facet;
            static time_input_facet *timeInputFacet = nullptr;
            static std::locale loc;
            if (!timeInputFacet)
            {
                timeInputFacet = new time_input_facet("%Y%m%d-%H:%M:%S");
                loc = std::locale(std::locale::classic(), timeInputFacet);
            }
            std::istringstream is(dateTimeString);
            is.imbue(loc);
            is >> m_DateTime;
        }

        const boost::posix_time::ptime ptime() const
        {
            return m_DateTime;
        }
    private:
        boost::posix_time::ptime m_DateTime;
    };

    std::ostream& operator<< (
        std::ostream& os,
        const FooTime::Time& dateTime
        )
    {
        return os << dateTime.ptime();
    }
}

int main()
{
    FooTime::Time t = "20100805-07:33:22";
    std::cout << t << std::endl;
}