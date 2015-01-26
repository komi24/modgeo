#include "testhe.hpp"

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

    /*v3 *p[5];
    p[0] = new v3(0,0,0);
    p[1] = new v3(0,0,1);
    p[2] = new v3(0,1,0);
    p[3] = new v3(0,1,1);
    p[4] = new v3(0,0.5,0.5);

    half_edge *he[16];
    facet *fct[4];

    fct[5] = new facet(p[0],p[1],p[2]); //base 1/2
    fct[6] = new facet(p[1],p[2],p[3]); //base 1/2

    for (int i=0; i<4; i++){
        fct[i]=new facet(p[5],p[i],p[(i+1)%5]);
        he[i] = new half_edge(p[5],fct[i]);
        he[i+4] = new half_edge(p[5],fct[i]);
        he[i]->setCcw(he[i+4]);
        he[i+4]->setCw(he[i]);
    }

    //création des opposite
    for (int i=0; i<4; i++){
        he[i+8] = new half_edge(p[i],fct[(i-1)%4]);

    }*/

}
