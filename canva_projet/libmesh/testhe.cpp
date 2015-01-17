#include "testhe.hpp"

#include <half_edge.hpp>
#include <facet.hpp>
#include <mesh.hpp>

using namespace proj;

TestHE::TestHE()
{
}

void TestHE::runTest(){
    //mesh m = new mesh;
    // p1 = 0 0 0;
    // p2 = 0 0 1;
    // p3 = 0 1 0;
    // p4 = 0 1 1;
    // p5 = 0 0.5 0.5;

    v3 *p[5];
    p[0] = new v3(0,0,0);
    p[1] = new v3(0,0,1);
    p[2] = new v3(0,1,0);
    p[3] = new v3(0,1,1);
    p[4] = new v3(0,0.5,0.5);

    half_edge *he[8];
    facet *fct[4];

    for (int i=0; i<4; i++){
        fct[i]=new facet(p[5],p[i],p[(i+1)%5]);
        half_edge tmp1(p[5],fct[i]);
        half_edge tmp2(p[5],fct[i]);
        std::cout << "ok" << std::endl;
    }

}
