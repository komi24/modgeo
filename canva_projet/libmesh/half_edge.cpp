#include "half_edge.hpp"
#include <facet.hpp>

namespace proj {

half_edge::half_edge()
{
}
half_edge::half_edge(v3* v,facet* f, half_edge* op,
                     half_edge* cc, half_edge* c)
{
    this->vert=v;
    this->fct=f;
    this->opposite=op;
    this->ccw=cc;
    this->cw=c;
}
half_edge::half_edge(v3* v,facet* f)
{
    this->vert=v;
    this->fct=f;
}
half_edge::half_edge(int v,facet* f)
{
    this->fct=f;
    this->vertex=v;
}
half_edge::half_edge(int v)
{
    this->vertex=v;
}
//half_edge::half_edge(mesh *m1){
//    this->m=m1;
//}

void half_edge::setVert(v3* v){
    this->vert=v;
}

void half_edge::setCcw(half_edge* h){
    this->ccw=h;
}

void half_edge::setCw(half_edge* h){
    this->cw=h;
}

void half_edge::setOpposite(half_edge* h){
    this->opposite=h;
}


// ********************************************* //
// ********************************************* //
//  Accessor
// ********************************************* //
// ********************************************* //
/** \brief Accessor to the vertex value */
v3& half_edge::getVert() {return *(this->vert); }
int half_edge::getVertex() {return this->vertex; }

/** \brief Accessor to the facet value */
facet& half_edge::getFct() {return *(this->fct); }

/** \brief Accessor to the opposite half-edge */
half_edge& half_edge::getOpposite() {return *(this->opposite); }

/** \brief Accessor to the counter clockwise next half-edge */
half_edge& half_edge::getCcw() {return *(this->ccw); }

/** \brief Accessor to the clockwise next (previous) half-edge */
half_edge& half_edge::getCw() {return *(this->cw); }

/** \brief Accessor to the Q matrix associated with the vertex */
//TODO check if it's not allready computed
matrix4& half_edge::getq() {return *(this->q); }

/** \brief Accessor to the Q matrix associated with the vertex */
/*v4& half_edge::getContraction() {
    v4* contraction = new v4;
    v3 buf=0.5*(m.get_vertices()[this->vertex]+this->opposite->vertex);
    contraction->x() = buf[0];
    contraction->y() = buf[1];
    contraction->z() = buf[2];
    contraction->w() = 1;
    return contraction;
}*/


//TODO is the same as get Q
//TO ERASE
matrix4 half_edge::getQ(){
    double a,b,c,d;
    v4 tp=this->fct->getq();
    a=tp[0];
    b=tp[1];
    c=tp[2];
    d=tp[3];
    // TODO loop on faces
    matrix4 *temp = new matrix4(a*a,a*b,a*c,a*d,
                               a*b,b*b,b*c,b*d,
                               a*c,b*c,c*c,c*d,
                               a*d,b*d,c*d,d*d);
    return *(temp);
}

/** \brief compute the matrix Q anyway and update it
 * for other half-edges associated to vert */
void half_edge::computeQ(){
    this->q = new matrix4;
    this->partiallyComputeQ(q,this->fct,10);//TODO REDO ERROR passage par référence ?
}

/** \brief compute the partial (for the facet) matrix Q
 * add it to curr and link this->q to curr and decrease i
 * and call itself for the next facet with i--
 * if i /= 0 (for test not to have infinite loop)
 * and if this->fct /= ofct (loop ended) */
void half_edge::partiallyComputeQ(matrix4 *curr, const facet *ofct, int i){
    if((i != 0) && (this->fct != ofct))
    {
        // TODO ERROR verify comparison between fct and ofct types
        double a,b,c,d;
        v4 tp=this->fct->getq();
        a=tp[0];
        b=tp[1];
        c=tp[2];
        d=tp[3];
        matrix4 tmp(a*a,a*b,a*c,a*d,
                    a*b,b*b,b*c,b*d,
                    a*c,b*c,c*c,c*d,
                    a*d,b*d,c*d,d*d);
        *(curr) += tmp;
        this->q = curr;
        this->ccw->opposite->partiallyComputeQ(curr,ofct,i-1);
    }
}

/** \brief Check if the HE is based on two vertices */
bool half_edge::he_use_vertices(v3* p1, v3* p2){
    return true;//TODO (p1==this->vert && p2==this->getCcw()) || (p2==this->vert && p1==this->getCcw()) ;
}


double half_edge::evaluate(){
    this->computeQ();
    //v4 contraction = getContraction();
    return 1.0;//contraction.dot((this->getQ() + this->getOpposite().getQ())*(contraction));
}

/** \brief Compare pair of vertice */
bool CompareHE::operator()(half_edge p1, half_edge p2)
{
    //return p1.evaluate()<p2.evaluate();
    return (p1.getVert()-p1.getOpposite().getVert()).norm2() < (p2.getVert()-p2.getOpposite().getVert()).norm2();
}

CompareHE::CompareHE(){
}

}
