#include "facet.hpp"

namespace proj
{
facet::facet()
{
}
facet::facet(v3 *p1, v3 *p2, v3 *p3){
    //this->u1=p1;
    //this->u2=p2;
    //this->u3=p3;
    //this->q=q+1;
}

facet::facet(int p1, int p2, int p3){
    this->u1=p1;
    this->u2=p2;
    this->u3=p3;
    //this->q=q+1;
}

void facet::set(int index, int value){
    switch (index) {
    case 0:
        this->u1=value;
    case 1:
        this->u2=value;
    case 2:
        this->u3=value;

        break;
    default:
        break;
    }
}

v4& facet::getq(){return q;}
}
