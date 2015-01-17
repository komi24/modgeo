#include "facet.hpp"

namespace proj
{
facet::facet()
{
}
facet::facet(v3 *p1, v3 *p2, v3 *p3){
    this->u1=p1;
    this->u2=p2;
    this->u3=p3;
    this->q=q+1;
}

v4& facet::getq(){return q;}
}
