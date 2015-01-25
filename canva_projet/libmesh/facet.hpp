#ifndef FACET_HPP
#define FACET_HPP

#include <v4.hpp>
#include <v3.hpp>
#include <iostream>


namespace proj
{

class mesh;

class facet
{
public:
    facet();
    // TODO rajouter un ordre de classement des points pour garantir uniciter de la représentation
    facet(v3* p1, v3* p2, v3* p3);
    facet(int p1, int p2, int p3, mesh* m);

    // ********************************************* //
    // ********************************************* //
    //  Accessors
    // ********************************************* //
    // ********************************************* //
    v4& getq();

    int get1();
    int getVertex(int index);

    // ********************************************* //
    // ********************************************* //
    //  Setters
    // ********************************************* //
    // ********************************************* //
    void set(int index, int value);


private:

    // ********************************************* //
    // ********************************************* //
    //  Internal data
    // ********************************************* //
    // ********************************************* //

    /** \brief Normal vector + shift */
    v4* q;
    /** \brief vertices */
    int u1,u2,u3;
};
}
#endif // FACET_HPP
