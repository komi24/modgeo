#include "facet.hpp"

#include <mesh.hpp>

namespace proj
{

facet::facet()
{
    q = new v4();
    std::cerr << "Error facet construction fault" << std::endl;
}

//TODO TO ERASE
facet::facet(v3 *p1, v3 *p2, v3 *p3){
    //this->u1=p1;
    //this->u2=p2;
    //this->u3=p3;
    //this->q=q+1;
    std::cerr << "Error facet construction fault" << std::endl;
}

facet::facet(int p1, int p2, int p3, mesh* m){
    this->u1=p1;
    this->u2=p2;
    this->u3=p3;
    v3 buf1 = m->vertex(p1);
    v3 buf2 = m->vertex(p1) - m->vertex(p2);
    v3 buf3 = m->vertex(p1) - m->vertex(p3);
    buf2 = buf2.cross(buf3);
    buf2 = buf2.normalized();
    this->q = new v4(buf2[0],buf2[1],buf2[2],-buf1.dot(buf2));
    //std::cout << "face " << p1 << " " << p2 << " " << p3 << " " << std::endl;
    //std::cout << "normal " << *q << std::endl;
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

int facet::getVertex(int index){
    switch (index) {
    case 0:
        return this->u1;
    case 1:
        return this->u2;
    case 2:
        return this->u3;

        break;
    default:
        break;
    }
}

v4& facet::getq(){return *q;}
int facet::get1(){return u1;}
}
