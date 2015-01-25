#include <mesh.hpp>
#include <facet.hpp>
#include <v3.hpp>
#include <matrix4.hpp>

#ifndef HALF_EDGE_HPP
#define HALF_EDGE_HPP

namespace proj
{
    class mesh;

/** \brief The half-ege data structure we chooose is an VE-structure
    according to the fact hat we will often have to find faces around
    one vetex. The structure of triangle strip will be of its own
    Ref : Using a generic programming for designing a Data Structure for Polyhedral Surfaces */
class half_edge
{
public:
    half_edge();
    half_edge(v3* v,facet* f, half_edge* op,
              half_edge* cc, half_edge* c);
    half_edge(v3* v,facet* f);

    void setVert(v3* v);

    half_edge(int v,facet* f); //new constructors
    half_edge(int v);
    static void setM(mesh* m1);

    void setVertex(int v);
    void setCcw(half_edge* h);
    void setCw(half_edge* h);
    void setOpposite(half_edge* h);
    void setFacet(facet* f);
    //TODO ERASE if not use
    //void setCcw(half_edge* h);
    //void setCcw(half_edge* h);

    // ********************************************* //
    // ********************************************* //
    //  Accessor
    // ********************************************* //
    // ********************************************* //
    /** \brief Accessor to the vertex value */
    v3& getVert();
    int getVertex();

    /** \brief Accessor to the facet value */
    facet& getFct();

    /** \brief Accessor to the opposite value */
    half_edge& getOpposite();
    half_edge* getOppositePtr();

    /** \brief Accessor to the counter clockwise next half-edge */
    half_edge& getCcw();

    /** \brief Accessor to the clockwise next (previous) half-edge */
    half_edge& getCw();
    half_edge* getCwPtr();

    /** \brief Accessor to the Q matrix associated with the vertex */
    matrix4& getq();

    /** \brief Accessor to the contrated vector associated with the vertex */
    v4* getContraction();


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
    /** \brief evaluate the vQv weight for the vertex*/
    double evaluate();

    /** \brief compute q for this half-edge and all
     * others associated to "vert" if needed */
    int computeQ();

    void updateFacet(mesh *m);

    //TODO TO ERASE matrix4 getQ();

    /** \brief Check if the HE is based on two vertices */
    bool he_use_vertices(v3* p1, v3* p2);

    static mesh* m;

private:

    // ********************************************* //
    // ********************************************* //
    //  Internal data
    // ********************************************* //
    // ********************************************* //

    //Check if it's better to use instance instead of pointer for some arguments
    //It seems to be better for arguments wich are tied to the instance
    //Just maybe facet and not q because q is linked to all other HE on the same vert
    /** Using pointers might save some time in destruction */
    /** \brief vertex */
    v3* vert;
    int vertex;
    /** \brief facet */
    proj::facet* fct;
    /** \brief opposite half-edge */
    half_edge* opposite;

    /** \brief next half-edge */
    half_edge* ccw;
    /** \brief previous half-edge */
    half_edge* cw;

    /** \brief matrix linked to the vertex vert */
    matrix4* q;


    // ********************************************* //
    // ********************************************* //
    //  Private methods
    // ********************************************* //
    // ********************************************* //

    /** \brief compute the partial (for the facet) matrix Q
     * add it to curr and link this->q to curr and decrease i
     * and call itself for the next facet with i--
     * if i /= 0 (for test not to have infinite loop)
     * and if this->fct /= ofct (loop ended) */
    void partiallyComputeQ(matrix4 *curr, const facet *ofct, int i);

};

class CompareHE{
public:
    CompareHE();
    bool operator()(half_edge *p1, half_edge *p2);
};
}
#endif // HALF_EDGE_HPP
