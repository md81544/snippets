// Shows how to use the .range() member function specifically

#include <string>

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/composite_key.hpp>

#include <string>
#include <iostream>

using namespace boost::multi_index;

struct Person
{
    size_t       Id;
    std::string  Name;
};
 
// Index "tags" used by Boost MultiIndex.
// Simply used to avoid referring to indices
// by their "magic" position numbers.
struct IdxPrimaryKey{};
struct IdxName{};

namespace bmi = boost::multi_index;

// Definition of our "database" format:
bmi::multi_index_container<
    Person,
    bmi::indexed_by<
        // The "primary key"
        bmi::ordered_unique<
            bmi::tag<IdxPrimaryKey>,
            bmi::member<
                Person, size_t, &Person::Id
            >
        >,
        // A simple key
        bmi::ordered_non_unique<
            bmi::tag<IdxName>,
            bmi::member<
                Person, std::string, &Person::Name
            >
        >
    >
> g_people;

int main()
{
    g_people.insert( {  1, "Helen"    } ); 
    g_people.insert( {  2, "Jessica"  } ); 
    g_people.insert( {  3, "Rachael"  } ); 
    g_people.insert( {  4, "Vicki"    } ); 
    g_people.insert( {  5, "Jenny"    } ); 
    g_people.insert( {  6, "Angie"    } ); 
    g_people.insert( {  7, "Yasmin"   } ); 
    g_people.insert( {  8, "Sarah"    } ); 
    g_people.insert( {  9, "Caroline" } ); 
    g_people.insert( { 10, "Mary"     } ); 
    g_people.insert( { 11, "Lisa"     } ); 
    g_people.insert( { 12, "Jane"     } ); 
    g_people.insert( { 13, "Louise"   } ); 
    g_people.insert( { 14, "Gaelle"   } ); 
    g_people.insert( { 15, "Michelle" } ); 
    g_people.insert( { 16, "Simone"   } ); 
    g_people.insert( { 17, "Fiona"    } ); 
    g_people.insert( { 18, "Eyrun"    } ); 
    g_people.insert( { 19, "Rachel"   } ); 
    g_people.insert( { 20, "Shannon"  } ); 


    auto& idx = g_people.get<IdxName>();

    // How to use the "range" member function. You provide two predicates (so poss-
    // ibly two lambdas) which perform any comparison you need. Note you can use
    // bmi::unbounded in place of either of these to give an open end to the range.
    auto t = idx.range(
        [](const std::string& s) {
            if (s >= "L") return true;
            return false;
            },
        bmi::unbounded // this could be a second lambda
        );
    auto it = t.first;
    for ( ; it != t.second; ++it )
    {
        std::cout << it->Name << std::endl;
    }

    return 0;
}



