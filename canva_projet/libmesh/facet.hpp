#ifndef FACET_HPP
#define FACET_HPP

#include <v4.hpp>
#include <v3.hpp>

namespace proj
{
class facet
{
public:
    facet();
private:

    // ********************************************* //
    // ********************************************* //
    //  Internal data
    // ********************************************* //
    // ********************************************* //

    /** \brief Normal vector + shift */
    v4 q;
    /** \brief vertices */
    v3* u1,u2,u3;
};
}
#endif // FACET_HPP
