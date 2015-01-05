#ifndef HALF_EDGE_HPP
#define HALF_EDGE_HPP

#include <facet.hpp>
#include <v3.hpp>

namespace proj
{

/** \brief The half-ege data structure we chooose is an VE-structure
    according to the fact hat we will often have to find faces around
    one vetex. The structure of triangle strip will be of its own
    Ref : Using a generic programming for designing a Data Structure for Polyhedral Surfaces */
class half_edge
{
public:
    half_edge();

    // ********************************************* //
    // ********************************************* //
    //  Accessor
    // ********************************************* //
    // ********************************************* //

    /** \brief Accesor to */


    // ********************************************* //
    // ********************************************* //
    //  Method for construction of the structure
    // ********************************************* //
    // ********************************************* //


    // ********************************************* //
    // ********************************************* //
    //  Method for simplification algorithm
    // ********************************************* //
    // ********************************************* //


private:

    // ********************************************* //
    // ********************************************* //
    //  Internal data
    // ********************************************* //
    // ********************************************* //

    /** Using pointers might save some time in destruction */
    /** \brief vertex */
    v3& vert;
    /** \brief facet */
    facet& fct;
    /** \brief opposite half-edge */
    half_edge& opposite;

    /** \brief next half-edge */
    half_edge& ccw;
    /** \brief previous half-edge */
    half_edge& cw;
};
}
#endif // HALF_EDGE_HPP
