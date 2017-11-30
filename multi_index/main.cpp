#include <boost/multi_index_container.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/composite_key.hpp>

#include <string>
#include <iostream>
#include <functional>

struct Vehicle
{
    size_t       Id;
    std::string  Make;
    std::string  Model;
    unsigned int YearMade;
    bool         SingleCylinder;
};

// Index "tags" used by Boost MultiIndex.
// Only purpose is to allow us to refer to indices
// by name rather than a "magic" positional number
struct IdxPrimaryKey{};
struct IdxYearMade{};
struct IdxMakeModel{};
struct IdxSingleCylinder{};

template<typename Tidx, typename Trecord>
void IterateOver(
    const Tidx& idx,
    std::function<void(const Trecord& rec)> func
    )
{
    auto it = idx.begin();
    while ( it != idx.end() )
    {
        func(*it++);
    }
}

int main()
{
    namespace bmi = boost::multi_index;

    // Definition of our "database" format:
    bmi::multi_index_container<
        Vehicle,
        bmi::indexed_by<
            // The "primary key"
            bmi::ordered_unique<
                bmi::tag<IdxPrimaryKey>,
                bmi::member<
                    Vehicle, size_t, &Vehicle::Id
                >
            >,
            // A simple key
            bmi::ordered_non_unique<
                bmi::tag<IdxYearMade>,
                bmi::member<
                    Vehicle, unsigned int, &Vehicle::YearMade
                >
            >,
            // Another simple key
            bmi::ordered_non_unique<
                bmi::tag<IdxSingleCylinder>,
                bmi::member<
                    Vehicle, bool, &Vehicle::SingleCylinder
                >
            >,
            // A composite key:
            bmi::ordered_non_unique<
                bmi::tag<IdxMakeModel>,
                bmi::composite_key<
                    Vehicle,
                    bmi::member<
                        Vehicle, std::string, &Vehicle::Make
                    >,
                    bmi::member<
                        Vehicle, std::string, &Vehicle::Model
                    >
                >
            >
        >
    > vehicles;

    vehicles.insert( { 1, "Vincent", "Rapide",    1950, false } );
    vehicles.insert( { 2, "BSA",     "Gold Star", 1958, false } );
    vehicles.insert( { 3, "Triumph", "Thruxton",  2010, false } );
    vehicles.insert( { 4, "Ariel",   "Square 4",  1959, false } );
    vehicles.insert( { 5, "Brough",  "Superior",  1925, false } );
    vehicles.insert( { 6, "Vincent", "Comet",     1951, true  } );
    vehicles.insert( { 7, "Norton",  "Commando",  1973, false } );

    // Iterate using "primary key" (ID) as index
    auto& idxId = vehicles.get<IdxPrimaryKey>();
    std::cout << "---------------------\n"
              << "Ordered by ID:\n" << std::endl;
    IterateOver<decltype(idxId), Vehicle>(
            idxId,
            [](const Vehicle& vec
        )
        {
            std::cout   << vec.Id << ": " << vec.Make
                        << " " << vec.Model << std::endl;
        }
    );

    std::cout << "---------------------\n"
              << "Ordered by year of manufacture:\n" << std::endl;
    // Iterate using year of manufacture as our index:
    auto& idxSimple = vehicles.get<IdxYearMade>();
    IterateOver<decltype(idxSimple), Vehicle>(
            idxSimple,
            [](const Vehicle& vec
        )
        {
            std::cout   << vec.YearMade << ": " << vec.Make
                        << " " << vec.Model << std::endl;
        }
    );

    std::cout << "---------------------\n"
              << "Ordered by marque then model:\n" << std::endl;
    // Iterate using our composite key (make/model):
    auto& idxComposite = vehicles.get<IdxMakeModel>();
    IterateOver<decltype(idxComposite), Vehicle>(
        idxComposite, [](const Vehicle& vec)
        {
            std::cout << vec.Make << " "
                      << vec.Model << std::endl;
        }
    );
    std::cout << "---------------------" << std::endl;

    {
        // Find a specific item:
        auto it = idxId.find(5); // should check result IRL!
        std::cout << "Item 5 is " << it->Make << " " << it->Model
                  << std::endl;
    }
    std::cout << "---------------------\n"
              << "Bikes made in the fifties:\n" << std::endl;

    {
        // Find a range of items -- bikes made in the 50s:
        auto it    = idxSimple.lower_bound( 1950 );
        auto itEnd = idxSimple.upper_bound( 1959 );
        while ( it != itEnd )
        {
            std::cout << it->Make << " " << it->Model << " ("
                      << it->YearMade << ")" << std::endl;
            ++it;
        }
    }
    std::cout << "---------------------\n"
              << "Single-cylinder bikes:\n" << std::endl;
    {
        // Find a range of items -- bikes with just one pot
        auto& idxSinglePot = vehicles.get<IdxSingleCylinder>();
        auto pr = idxSinglePot.equal_range( true );
        auto it = pr.first;
        auto itEnd = pr.second;
        while ( it != itEnd )
        {
            std::cout << it->Make << " " << it->Model << " ("
                      << it->YearMade << ")" << std::endl;
            ++it;
        }
    }
    std::cout << "---------------------" << std::endl;

    return 0;
}
