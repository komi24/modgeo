/*
**    This program is free software: you can redistribute it and/or modify
**    it under the terms of the GNU General Public License as published by
**    the Free Software Foundation, either version 3 of the License, or
**    (at your option) any later version.
**
**   This program is distributed in the hope that it will be useful,
**    but WITHOUT ANY WARRANTY; without even the implied warranty of
**    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**    GNU General Public License for more details.
**
**    You should have received a copy of the GNU General Public License
**    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/



#include <mesh.hpp>
#include <mesh_io.hpp>

#include <matrix3.hpp>

#include <cmath>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <map>
#include <list>
#include <assert.h>
#include <cstdlib>
#include <set>

//TODO #include <half_edge.hpp>

using namespace std;

namespace proj
{

    mesh::mesh(){
        half_edge::setM(this);
    }

    const vector<v3>& mesh::get_vertices() const{return v_vertices;}
    const vector<v3>& mesh::get_normal() const{return v_normal;}
    const vector<v3>& mesh::get_color() const{return v_color;}
    /** TODO  update the connectivity with half edge structure if needed */
    const vector<int>& mesh::get_connectivity() const{return v_connectivity;}

    vector<v3>& mesh::get_vertices() {return v_vertices;}
    vector<v3>& mesh::get_normal() {return v_normal;}
    vector<v3>& mesh::get_color() {return v_color;}
    vector<int>& mesh::get_connectivity() {return v_connectivity;}

    void mesh::load_file(const string &filename)
    {
        if(filename.find(".off")!=string::npos)
            *this=mesh_io::load_off_file(filename);
        else if(filename.find(".obj")!=string::npos)
            *this=mesh_io::load_obj_file(filename);
        else
        {
            stringstream msg;
            msg<<"Error, file format unknown ["<<filename<<"]";
            proj::exception_proj(msg.str(),__FILE__,__FUNCTION__,__LINE__);
        }
    }


    // ********************************************* //
    // ********************************************* //
    //  Selection
    // ********************************************* //
    // ********************************************* //

    /**
     * Euclidean length between 2 vertex
     */
    double euclideanLength(v3 a, v3 b) {
        return sqrt(pow(b.x()-a.x(),2) + pow(b.y()-a.y(),2) + pow(b.z()-a.z(),2));
    }

    /**
     *  Selection criteria algorithm for edge collapse
     */
    bounded_priority_queue<vertexpair> mesh::selection(int n){
        bounded_priority_queue<vertexpair> pq(n);        
        half_edge* he;
        half_edge oppositeHe;

        for(list<half_edge*>::iterator pos = h_edges.begin(); pos != h_edges.end(); pos++) {
            he = *pos;
            oppositeHe = he->getOpposite();
            if(he->getVertex() != oppositeHe.getVertex()) {
                vertexpair auxpair(he->getVertex(), oppositeHe.getVertex(), euclideanLength(v_vertices[he->getVertex()], v_vertices[oppositeHe.getVertex()]));
                pq.push(auxpair);
            }
        }

        return pq;
    }

    // ********************************************* //
    // ********************************************* //
    //  Simplification
    // ********************************************* //
    // ********************************************* //

    /**
     * Updates the vectors by removing the vertex M and the edge [MN]
     */
    vector<int> mesh::updateTables(vector<int> v, int m, int n, int *update, int *error)
    {
        v_vertices.erase(v_vertices.begin() + m);
        v_normal.erase(v_normal.begin() + m);

        int a, b, c;
        bool am, an, bm, bn, cm, cn;

        size_t vSize = v.size();
        int indexToDelete1 = -1;
        int indexToDelete2 = -1;

        for (size_t i=0;i<vSize;i=i+3) {
            a = v[i];
            b = v[i+1]; // 3 vertices from the face
            c = v[i+2];

            if (a==m) am = true; else am=false;
            if (a==n) an = true; else an=false;
            if (b==m) bm = true; else bm=false;
            if (b==n) bn = true; else bn=false;
            if (c==m) cm = true; else cm=false;
            if (c==n) cn = true; else cn=false;

            if(!am && !an && !bm && !bn && !cm && !cn) {
                // No vertex is changing, we do not modify this face
            } else if ((am || bm || cm) && (an || bn || cn)) {
                // The two vertices are in the triangle, we keep their indices to erase them
                if(indexToDelete1 == -1)
                    indexToDelete1 = i;
                else if(indexToDelete2 == -1)
                    indexToDelete2 = i;
                else {
                    *error = 1;
                    cout << "Error in connectivity table!!!" << endl;
                }
            } else {
                // Only one vertex will change, we will take care of it after
            }
        }

        // We erase the faces
        if(indexToDelete1 != -1) {
            v.erase(v.begin()+indexToDelete1,v.begin()+indexToDelete1+3);
            *update = 1;

            if(indexToDelete2 != -1)
                v.erase(v.begin()+indexToDelete2-3,v.begin()+indexToDelete2);

            // We update connectivity, to keep correspondance with the vertices vector
            for (size_t j = 0; j < v.size(); ++j) {
                if(v[j] > min(m,n))
                    v[j] = v[j] - 1;
            }
        }

        return v;
    }

    /**
     * Updates the half edge list by removing the vertex M and the edge [MN]
     */
    list<half_edge*> mesh::updateHalfedges(list<half_edge*> he_list, int m, int n, int *update) {
        int founded = 0;
        half_edge* he;

        /** First, we look for the half edge with vertex m and ending in n */
        for(list<half_edge*>::iterator pos = he_list.begin(); pos != he_list.end() && founded != 1; pos++) {
            he = *pos;
            if(he->getVertex() == m) {
                if(he->getOpposite().getVertex() == n){
                    founded = 1;
                }
            }
        }

        if(founded == 1) { /* We simplify the edge [MN] */
            half_edge mNextOpposite = he->getCw().getOpposite();
            half_edge mPreviousOpposite = he->getCw().getCw().getOpposite();
            half_edge nNextOpposite = he->getOpposite().getCw().getOpposite();
            half_edge nPreviousOpposite = he->getOpposite().getCw().getCw().getOpposite();

            // The opposite of the next of M will be the opposite of the previous to M
            he->getCw().setOpposite(&mPreviousOpposite);

            // The opposite of the previous to M will be the opposite of the next of M
            he->getCw().getCw().setOpposite(&mNextOpposite);

            // The opposite of the next of N will be the opposite of the previous to N
            he->getOpposite().getCw().setOpposite(&nPreviousOpposite);

            // The opposite of the previous to N will be the opposite of the next of N
            he->getOpposite().getCw().getCw().setOpposite(&nNextOpposite);

            // We erase from the list the both half edges between M and N; both nexts; and both previous
            for(list<half_edge*>::iterator pos = he_list.begin(); pos != he_list.end(); pos++) {
                he = *pos;
                if( (he->getVertex() == m && he->getOpposite().getVertex() == n)                   // half-edge from m to n
                  || (he->getVertex() == n && he->getOpposite().getVertex() == m)                  // half-edge from n to m
                  || (he->getVertex() == n && he->getCw().getCw().getVertex() == m)                // next of half-edge from m to n
                  || (he->getVertex() == m && he->getCw().getCw().getVertex() == n)                // next of half-edge from n to m
                  || (he->getCw().getVertex() == m && he->getCw().getCw().getVertex() == n)        // previous of half-edge from m to n
                  || (he->getCw().getVertex() == n && he->getCw().getCw().getVertex() == m) ) {    // previous of half-edge from n to m

                    pos = he_list.erase(pos);

                }
            }

            // We update the half edges list, to keep correspondance with the vertices vector
            for (list<half_edge*>::iterator pos = he_list.begin(); pos != he_list.end(); pos++) {
                he = *pos;
                if(he->getVertex() > min(m,n))
                    he->setVertex(he->getVertex()-1);
            }


            v_vertices.erase(v_vertices.begin() + min(m,n));
            v_normal.erase(v_normal.begin() + min(m,n));
        }

        *update = founded;
        return he_list;
    }

    vector<int> mesh::halfedgesToConnectivity(list<half_edge*> he_list) {
        vector<int> result;
        list<half_edge*>::iterator pos;

        for(pos = he_list.begin(); pos != he_list.end(); pos++) {
            half_edge* he = *pos;
            result.push_back(he->getVertex());
            result.push_back(he->getCw().getVertex());
            result.push_back(he->getCw().getCw().getVertex());
        }

        return result;
    }

    void mesh::simplification() {

        cout << "Size of vertices: " << v_vertices.size() << endl;
        cout << "Size of half edges: " << h_edges.size() << endl;
        cout << "Size of connectivity: " << v_connectivity.size() << endl;
        cout << "\n";

        int numToDelete = 10;

        bounded_priority_queue<vertexpair> bounded_pq = selection(numToDelete);
        priority_queue<vertexpair> pq = bounded_pq.pop_all();

        vector<vertexpair> vertexvector;
        vertexvector.resize(numToDelete);

        for (size_t i = 0; i < vertexvector.size(); ++i) {
            vertexpair tmp = pq.top();
            pq.pop();
            vertexvector[i] = tmp;
        }

        int update = 0;
        int k;

        for(int i=0;i<numToDelete;++i) {

            if(update == 1) {
                // We have to update the vertices in the table
                for (size_t j = i; j < vertexvector.size(); ++j) {
                    if(vertexvector[j].vert1 > k)
                        vertexvector[j].vert1 = vertexvector[j].vert1 - 1;
                    if(vertexvector[j].vert2 > k)
                        vertexvector[j].vert2 = vertexvector[j].vert2 - 1;
                }
                update = 0;
            }


            vertexpair vertexToDelete = vertexvector[i];

            h_edges = updateHalfedges(h_edges, vertexToDelete.vert1, vertexToDelete.vert2, &update);
            v_connectivity = halfedgesToConnectivity(h_edges);

            k = min(vertexToDelete.vert1, vertexToDelete.vert2);


            cout << "Size of vertices: " << v_vertices.size() << endl;
            cout << "Size of half edges: " << h_edges.size() << endl;
            cout << "Size of connectivity: " << v_connectivity.size() << endl;
            cout << "\n";
        }

    }




    // ********************************************* //
    // ********************************************* //
    //  Normal
    // ********************************************* //
    // ********************************************* //

    void mesh::compute_normal()
    {
       v_normal=get_normal_per_vertex();
    }

    mesh operator+(const v3& x,const mesh& m){return m+x;}
    mesh operator+(const mesh& m,const v3& x){mesh m2=m; m2+=x; return m2;}
    mesh& mesh::operator+=(const v3& x)
    {
        for(unsigned int k=0,N=v_vertices.size();k<N;++k)
            v_vertices[k]+=x;
        return *this;
    }

    mesh operator-(const mesh& m,const v3& x){mesh m2=m; m2-=x; return m2;}
    mesh& mesh::operator-=(const v3& x)
    {
        for(unsigned int k=0,N=v_vertices.size();k<N;++k)
            v_vertices[k]-=x;
        return *this;
    }

    mesh operator*(const double& s,const mesh& m){mesh m2=m; m2*=s; return m2;}
    mesh operator*(const mesh& m,const double& s){return s*m;}
    mesh& mesh::operator*=(const double& s)
    {
        for(unsigned int k=0,N=v_vertices.size();k<N;++k)
            v_vertices[k]*=s;
        return *this;
    }

    void mesh::auto_scale(const double& scale)
    {

        //find min-max position
        v3 xmin=v_vertices[0];
        v3 xmax=xmin;
        for(unsigned int k=1,N=v_vertices.size();k<N;++k)
        {
            const v3& x=v_vertices[k];

            if(xmin.x()>x.x())xmin.x()=x.x();
            if(xmin.y()>x.y())xmin.y()=x.y();
            if(xmin.z()>x.z())xmin.z()=x.z();

            if(xmax.x()<x.x())xmax.x()=x.x();
            if(xmax.y()<x.y())xmax.y()=x.y();
            if(xmax.z()<x.z())xmax.z()=x.z();
        }

        v3 u=xmax-xmin;
        double s=max(u.x(),u.y());

        //scale positions to fit in screen
        *this -= xmin;
        *this *= scale*2.0/s;
        *this += v3(-scale,-scale,-scale);

    }

    void mesh::fill_color(const v3& c)
    {
        v_color.resize(v_vertices.size());
        for(unsigned int k=0,N=v_vertices.size();k<N;++k)
            v_color[k]=c;
    }
    void mesh::scale(const double& sx,const double& sy,const double& sz)
    {
        for(unsigned int k=0,N=v_vertices.size();k<N;++k)
            v_vertices[k].scale(sx,sy,sz);
    }
    void mesh::fill_color_xyz()
    {
        v3 xmin=v_vertices[0];
        v3 xmax=xmin;
        for(unsigned int k=1,N=v_vertices.size();k<N;++k)
        {
            const v3& x=v_vertices[k];

            if(xmin.x()>x.x())xmin.x()=x.x();
            if(xmin.y()>x.y())xmin.y()=x.y();
            if(xmin.z()>x.z())xmin.z()=x.z();

            if(xmax.x()<x.x())xmax.x()=x.x();
            if(xmax.y()<x.y())xmax.y()=x.y();
            if(xmax.z()<x.z())xmax.z()=x.z();
        }
        v3 u=xmax-xmin;

        v_color.resize(v_vertices.size());
        for(unsigned int k=0,N=v_vertices.size();k<N;++k)
        {
            v3 x=v_vertices[k]-xmin;
            v_color[k]=v3(x.x()/u.x(),x.y()/u.y(),x.z()/u.z());
        }

    }
    void mesh::fill_color_normal()
    {
         v_color.resize(v_vertices.size());
         for(unsigned int k=0,N=v_normal.size();k<N;++k)
         {
             v3 n=v_normal[k];
             v_color[k]=v3(fabs(n.x()),fabs(n.y()),fabs(n.z()));
         }
    }

    const v3& mesh::vertex(const unsigned int& index) const
    {
        //check index
        if(index>=v_vertices.size())
        {
            ostringstream msg;
            msg<<"Error index "<<index<<" outside bounds of size:"<<v_vertices.size();
            throw proj::exception_mesh(msg.str(),__FILE__,__PRETTY_FUNCTION__,__LINE__);
        }
        //return index
        return v_vertices[index];
    }
    v3& mesh::vertex(const unsigned int& index)
    {
        //check index
        if(index>=v_vertices.size())
        {
            ostringstream msg;
            msg<<"Error index "<<index<<" outside bounds of size:"<<v_vertices.size();
            throw proj::exception_mesh(msg.str(),__FILE__,__PRETTY_FUNCTION__,__LINE__);
        }
        //return index
        return v_vertices[index];
    }

    const v3& mesh::normal(const unsigned int& index) const
    {
        //check index
        if(index>=v_normal.size())
        {
            ostringstream msg;
            msg<<"Error index "<<index<<" outside bounds of size:"<<v_normal.size();
            throw proj::exception_mesh(msg.str(),__FILE__,__PRETTY_FUNCTION__,__LINE__);
        }
        //return index
        return v_normal[index];
    }
    v3& mesh::normal(const unsigned int& index)
    {
        //check index
        if(index>=v_normal.size())
        {
            ostringstream msg;
            msg<<"Error index "<<index<<" outside bounds of size:"<<v_normal.size();
            throw proj::exception_mesh(msg.str(),__FILE__,__PRETTY_FUNCTION__,__LINE__);
        }
        //return index
        return v_normal[index];
    }

    const v3& mesh::color(const unsigned int& index) const
    {
        //check index
        if(index>=v_color.size())
        {
            ostringstream msg;
            msg<<"Error index "<<index<<" outside bounds of size:"<<v_color.size();
            throw proj::exception_mesh(msg.str(),__FILE__,__PRETTY_FUNCTION__,__LINE__);
        }
        //return index
        return v_color[index];
    }
    v3& mesh::color(const unsigned int& index)
    {
        //check index
        if(index>=v_color.size())
        {
            ostringstream msg;
            msg<<"Error index "<<index<<" outside bounds of size:"<<v_color.size();
            throw proj::exception_mesh(msg.str(),__FILE__,__PRETTY_FUNCTION__,__LINE__);
        }
        //return index
        return v_color[index];
    }

    const v2& mesh::texture(const unsigned int& index) const
    {
        //check index
        if(index>=v_texture.size())
        {
            ostringstream msg;
            msg<<"Error index "<<index<<" outside bounds of size:"<<v_texture.size();
            throw proj::exception_mesh(msg.str(),__FILE__,__PRETTY_FUNCTION__,__LINE__);
        }
        //return index
        return v_texture[index];
    }
    v2& mesh::texture(const unsigned int& index)
    {
        //check index
        if(index>=v_texture.size())
        {
            ostringstream msg;
            msg<<"Error index "<<index<<" outside bounds of size:"<<v_texture.size();
            throw proj::exception_mesh(msg.str(),__FILE__,__PRETTY_FUNCTION__,__LINE__);
        }
        //return index
        return v_texture[index];
    }

    const int& mesh::connectivity(const unsigned int& index) const
    {
        /** TODO  update the connectivity with half edge structure if needed */
        /** TODO */
        /** TODO */

        //check index
        if(index>=v_connectivity.size())
        {
            ostringstream msg;
            msg<<"Error index "<<index<<" outside bounds of size:"<<v_color.size();
            throw proj::exception_mesh(msg.str(),__FILE__,__PRETTY_FUNCTION__,__LINE__);
        }
        //return index
        return v_connectivity[index];
    }
    int& mesh::connectivity(const unsigned int& index)
    {
        /** TODO  update the connectivity with half edge structure if needed */
        /** TODO */
        /** TODO */

        //check index
        if(index>=v_connectivity.size())
        {
            ostringstream msg;
            msg<<"Error index "<<index<<" outside bounds of size:"<<v_color.size();
            throw proj::exception_mesh(msg.str(),__FILE__,__PRETTY_FUNCTION__,__LINE__);
        }
        //return index
        return v_connectivity[index];
    }

    unsigned int mesh::number_of_triangle() const
    {
        return v_connectivity.size()/3;
    }
    unsigned int mesh::number_of_vertices() const
    {
        return v_vertices.size();
    }

    void mesh::apply(const proj::matrix3 R)
    {
        for(unsigned int k=0,N=v_vertices.size();k<N;++k)
            v_vertices[k]=R*v_vertices[k];
    }

    void mesh::add_vertex(const v3& vertex_to_add){v_vertices.push_back(vertex_to_add);}
    void mesh::add_texture(const v2& texture_to_add){v_texture.push_back(texture_to_add);}
    void mesh::add_triangle(const int u0,const int u1,const int u2)
    {
        /** TODO add triangle to the half-edge structure */
        /** TODO */
        /** TODO */
        /** TODO */
        v_connectivity.push_back(u0);
        v_connectivity.push_back(u1);
        v_connectivity.push_back(u2);
    }

    /** TODO our version */
    void mesh::add_triangleHE(const int u0,const int u1,const int u2){

        //Sort vertices according to ccw order

        //Create three HE and link them together according to previous step

        //look into he_list if the opposite is allready built using he.he_use_vert
    }

    void mesh::buildHEDS(){

        //Copy all triangle in a todo list
        std::deque<int> todoList(v_connectivity.begin(),v_connectivity.end());
        std::deque<half_edge*> boundary;//deque because of the iterator invalidation rule
        int p[3];
        half_edge *he[6];
        facet *curr;

        cout << "todolist "<<todoList.size() << endl;


        //TODO ERASE for(std::deque<int>::iterator ite = todoList.begin(); ite!=todoList.end(); ite++)
        //    std::cout << *ite << std::endl;

        //start with one triangle tranfered to the HE list /processing queue (boundary)

        //std::cout << "tdolist"<<endl;
        //for(std::deque<int>::iterator ite = todoList.begin(); ite!=todoList.end(); ite++)
            //std::cout << (*ite) << std::endl;

        for(int i=0; i<3; i++) {
            p[i]=todoList.front();
            todoList.pop_front();
        }

        curr = new facet(p[0],p[1],p[2],this);
        //create  3 inner HE and 3 outter HE and link opposites
        for(int i=0; i<3; i++){
            he[i] = new half_edge(p[i],curr);//inner
            he[i+3] = new half_edge(p[(i+1)%3]);//outter
            he[i]->setOpposite(he[i+3]);
            he[i+3]->setOpposite(he[i]);
            //Save inner HE in this->h_edges
            this->h_edges.push_back(he[i]);
        }
        //link inner HE and push_back outter HE in boundary
        for(int i=0; i<3; i++){
            he[i]->setCw(he[(i+1)%3]);
            boundary.push_back(he[i+3]);
        }
        //std::cout << std::endl << "todoList.front()" << std::endl;
        //TODO ERASE for(std::deque<int>::iterator ite = todoList.begin(); ite!=todoList.end(); ite++)
            //std::cout << *ite << std::endl;

        //search loop
        std::deque<int>::iterator buf[3];//buffer of the current triangle
        while(boundary.size()!=0){
            he[0]=boundary.front();
            p[0]=he[0]->getVertex();
            p[1]=he[0]->getOpposite().getVertex();
            //look for a triangle in todoList with p0 p1 as an edge
            std::deque<int>::iterator it = todoList.begin();
            int found1 = -3;//the choice of 3 is because i<3 and addition is fast
            int found2 = -3;
            //loop as long as we don't find triangle and there is still other triangles
            while(((found1+found2)<0) && (it != todoList.end())){
                //bufferize one triangle
                found1 = -3;
                found2 = -3;
                for(int i=0; i<3; i++){
                    found1 = (*it == p[0]) ? i : found1;//TODO take into account ABB (double occurence)
                    found2 = (*it == p[1]) ? i : found2;
                    buf[i]=it++;
                }
            }
            if(found1+found2>0){
                //If a triangle with the two vertices have been found
                //find the other vertex
                p[2]=*(buf[3-found1-found2]);
                //TODO ERASE std::cout << endl << "TAILLE ok1 = " << todoList.size() << endl;
                //std::cout << "TAILLE ok1 = " << h_edges.size() << endl;
                //std::cout << " p[0] " << p[0] << " p[1] " << p[1] << " p[2] " << p[2] << endl;
                //std::cout << "TAILLE ok1 = " << boundary.size() << endl;
                //for(std::deque<half_edge*>::iterator ite = boundary.begin(); ite!=boundary.end(); ite++)
                //    std::cout << (*ite)->getVertex() << "  " << (*ite)->getOpposite().getVertex() << std::endl;
                //Link inner HE and outter HE
                curr = new facet(p[0],p[1],p[2],this);
                //create  2 inner HE and 2 outter HE and link opposites
                //and push_back outter HE in boundary
                //and push_back inner HE in h_edges
                h_edges.push_back(he[0]);
                he[0]->setFacet(curr);
                for(int i=1; i<3; i++){
                    he[i] = new half_edge(p[i],curr);
                    he[i+3] = new half_edge(p[(i+1)%3]);
                    he[i]->setOpposite(he[i+3]);
                    he[i+3]->setOpposite(he[i]);
                    boundary.push_back(he[i+3]);
                    h_edges.push_back(he[i]);
                }

                //link inner HE
                for(int i=0; i<3; i++){
                    he[i]->setCw(he[(i+1)%3]);
                }
                //erase the triangle from todolist
                todoList.erase(buf[0],++buf[2]);
            }
            //if no triangle found erase the HE if not linkable
            if(found1+found2<0){
                //TODO ERASE std::cout << endl << "TAILLE ok = " << todoList.size() << endl;
                //std::cout <<"TAILLE ok = " << boundary.size() << endl;
                //std::cout << "TAILLE ok = " << h_edges.size() << " ff "<< found1<< " " <<found2<< endl;
                //std::cout << " p[0] " << he[0]->getVertex() << " p[1] " << he[0]->getOpposite().getVertex() << endl;
                //for(std::deque<half_edge*>::iterator ite = boundary.begin(); ite!=boundary.end(); ite++)
                //    std::cout << (*ite)->getVertex() << "  " << (*ite)->getOpposite().getVertex() << std::endl;

                //check if some outter HE can be opposite-linked to existing HE
                std::deque<half_edge*>::iterator it1 = boundary.begin();
                half_edge h1 = *(*it1);
                half_edge *h2 = h1.getOppositePtr();
                half_edge *h3 = he[0]->getOppositePtr();
                int compt =1;
                //std::cout << "bla" << endl;
                //std::cout << " hes "<< h3->getVertex() << " " << h2->getVertex() << std::endl;
                //std::cout << " hes "<< he[0]->getVertex() << " " << h1.getVertex() << std::endl;
                while(((h1.getVertex()!=h3->getVertex())
                      ||(h2->getVertex()!=he[0]->getVertex()))
                      &&(++it1 != boundary.end())){
                    //it1++;
                    compt++;
                    //std::cerr << compt << "bla0 " << boundary.size()<< endl;
                    h1 = *(*it1);
                    //std::cerr << "bla1" << endl;
                    h2 = h1.getOppositePtr();
                    //std::cerr << "bla2 " << h2->getVertex()<< endl;
                    //std::cerr << "bla2 " << h3->getVertex()<< endl;
                    //std::cerr << "bla2 " << h1.getVertex()<< endl;
                }
                //std::cerr << "bla3" << endl;
                if((h1.getVertex()==h3->getVertex())
                        &&(h2->getVertex()==he[0]->getVertex())){
                    //std::cout << "bla" << endl;
                    //std::cout << " hes "<< h3->getVertex() << " " << h2->getVertex() << std::endl;
                    //std::cout << " hes "<< he[0]->getVertex() << " " << h1.getVertex() << std::endl;
                    //for(std::list<half_edge*>::iterator ite = h_edges.begin(); ite!=h_edges.end(); ite++)
                        //std::cout << (*ite)->getVertex() << "  " << (*ite)->getOpposite().getVertex() << std::endl;
                    //delete both outters HE and link inners HE
                    delete *it1;
                    boundary.erase(it1);
                    delete he[0];
                    h3->setOpposite(h2);
                    h2->setOpposite(h3);
                }else{
                    //std::cout << "non orientable ou bord ERROR !!!!!!!!!!" <<std::endl;
                    delete he[0];
                }
            }
            //size of boundary --1 / Enlever le premier terme
            boundary.pop_front();
            //cout << "*";//h_edges.size() << endl;
        }
        //cout << endl <<"he size "<< h_edges.size() << endl;
        //for(std::list<half_edge*>::iterator ite = h_edges.begin(); ite!=h_edges.end(); ite++)
            //std::cout << (*ite)->getVertex() << "  " << (*ite)->getOpposite().getVertex() << std::endl;

        //this->buildHeap();
    }

    void mesh::buildHeap(){
        //cerr << "0k1.1 "<< pq2->size() << endl;
/*        while(!pq2->empty()){
            cerr << "0k1.1 "<< pq2->size() << endl;
            pq2->pop();
            cerr << pq2->size()<<endl;
        }*/
        pq2 = new priority_queue<half_edge*,std::vector<half_edge*>,CompareHE>();
        cerr << "0k1.2 "<<endl;
        for(std::list<half_edge*>::iterator ite = h_edges.begin(); ite!=h_edges.end(); ite++)
            pq2->push(*ite);
        //cout << (pq2->top())->getVertex() << "  " << (pq2->top())->getOpposite().getVertex() << std::endl;
        //cout << "val " << (pq2->top())->evaluate() << std::endl;
    }

    /** \brief collapse the given edge */
    void mesh::edgeCollapse(half_edge *h){
        if(h->getOppositePtr()->getCwPtr()->getCwPtr()->getVertex() == h->getCwPtr()->getCwPtr()->getVertex())
        {
            cerr << "limite" <<endl;
            return;
        }
        v4 *contract = h->getContraction(this);
        int p1[3];
        int xoxo=1000;
        /* TO ERASE
        cout << "ok22 " << h->getOppositePtr()->getCwPtr()->getCwPtr()->getVertex() << endl;
        cout << "ok23 " << h->getOppositePtr()->getCwPtr()->getVertex() << endl;
        cout << "ok24 " << h->getOppositePtr()->getVertex() << endl;

        cout << "ok32 " << h->getCwPtr()->getCwPtr()->getVertex() << endl;
        cout << "ok23 " << h->getCwPtr()->getVertex() << endl;
        cerr << "ok34 " << h->getVertex() << endl;
        cin >> xoxo;
        cout << "ok" <<endl;
        cout << "wating "<< h_edges.size() << endl;
        cout << "ok21 " << h->getVertex() << "  " << h->getOppositePtr()->getVertex() << endl;
        cout << "test00" <<endl;
        cin >> xoxo;
        cout << "ok" <<endl;*/

        this->v_vertices[h->getVertex()]=contract->to_v3();
        //cout << *contract <<endl;
        //cout << "test10" <<endl;
        //cin >> xoxo;
        //cout << "ok" <<endl;

        half_edge *curr = h->getOppositePtr();// TO DO delete and erase from vector op.vertex
        curr->setVertex(h->getVertex());
        curr = curr->getOppositePtr()->getCwPtr();
        while ((curr != h->getOppositePtr()) && (xoxo-- > 0)){
            /* TO ERASE cout << "testk" << xoxo-- <<endl;
            cout << "ok22 " << h->getOppositePtr()->getCwPtr()->getCwPtr()->getVertex() << endl;
            cout << "ok23 " << h->getOppositePtr()->getCwPtr()->getVertex() << endl;
            cout << "ok24 " << h->getOppositePtr()->getVertex() << endl;

            cout << "ok32 " << h->getCwPtr()->getCwPtr()->getVertex() << endl;
            cout << "ok23 " << h->getCwPtr()->getVertex() << endl;
            cout << "ok34 " << h->getVertex() << endl;
            cout << "wating "<< endl;
            cin >> xoxo;
            cout << "ok" <<endl;*/
            curr->setVertex(h->getVertex());
            curr->updateFacet(this);
            curr = curr->getOppositePtr()->getCwPtr();
        }
        if(xoxo <0){
            cerr << "oups !!!!!!" << endl;
            return;
        }

        //update facets around h
        curr = h;
        curr = curr->getOppositePtr()->getCwPtr();
        //cout << "test2" <<endl;
        //cin >> xoxo;
        //cout << "ok" <<endl;
        xoxo=1000;
        while ((curr != h) && (xoxo--!=0)) {
            /*cout << "testR" << xoxo-- <<endl;
            cout << "ok22 " << h->getOppositePtr()->getCwPtr()->getCwPtr()->getVertex() << endl;
            cout << "ok23 " << h->getOppositePtr()->getCwPtr()->getVertex() << endl;
            cout << "ok24 " << h->getOppositePtr()->getVertex() << endl;

            cout << "ok32 " << h->getCwPtr()->getCwPtr()->getVertex() << endl;
            cout << "ok23 " << h->getCwPtr()->getVertex() << endl;
            cout << "ok34 " << h->getVertex() << endl;
            cout << "wating "<< endl;
            cin >> xoxo;
            cout << "ok" <<endl;*/
            curr->updateFacet(this);
            curr = curr->getOppositePtr()->getCwPtr();
        }
        if(xoxo <0){
            cerr << "oups !!!!!!" << endl;
            return;
        }
        //cout << "test3" <<endl;
        //cin >> xoxo;
        //cout << "ok" <<endl;

        //modify structure
        h->getCwPtr()->getOppositePtr()->setOpposite(h->getCwPtr()->getCwPtr()->getOppositePtr());
        h->getCwPtr()->getCwPtr()->getOppositePtr()->setOpposite(h->getCwPtr()->getOppositePtr());

        h->getOppositePtr()->getCwPtr()->getOppositePtr()->setOpposite(h->getOppositePtr()->getCwPtr()->getCwPtr()->getOppositePtr());
        h->getOppositePtr()->getCwPtr()->getCwPtr()->getOppositePtr()->setOpposite(h->getOppositePtr()->getCwPtr()->getOppositePtr());

        /*cout << "ok22 " << h->getOppositePtr()->getCwPtr()->getCwPtr()->getVertex() << endl;
        cout << "ok23 " << h->getOppositePtr()->getCwPtr()->getVertex() << endl;
        cout << "ok24 " << h->getOppositePtr()->getVertex() << endl;

        cout << "ok32 " << h->getCwPtr()->getCwPtr()->getVertex() << endl;
        cout << "ok23 " << h->getCwPtr()->getVertex() << endl;
        cout << "ok34 " << h->getVertex() << endl;
        cout << "exited"<<endl;*/

        //TODO delete
        h_edges.remove(h->getOppositePtr()->getCwPtr()->getCwPtr());
        h_edges.remove(h->getOppositePtr()->getCwPtr());
        h_edges.remove(h->getOppositePtr());

        h_edges.remove(h->getCwPtr()->getCwPtr());
        h_edges.remove(h->getCwPtr());
        h_edges.remove(h);

    }

    void mesh::simplification2(){

        half_edge::m =this;
        std::set<facet*> forbidden;
        int inut;
        buildHeap();
        for (int i=0 ; i< 10; i++){
            //cin >> inut;
            //cerr << "ok3"<<endl;
            if(forbidden.count(this->pq2->top()->getFacet())==0)
            {
                forbidden.insert(pq2->top()->getFacet());
                forbidden.insert(pq2->top()->getOppositePtr()->getFacet());
                forbidden.insert(pq2->top()->getCwPtr()->getOppositePtr()->getFacet());
                forbidden.insert(pq2->top()->getCwPtr()->getCwPtr()->getOppositePtr()->getFacet());

                edgeCollapse(this->pq2->top());
                v_connectivity = halfedgesToConnectivity(h_edges);
                cerr << v_connectivity.size() <<endl;
            } else {
                cerr << "hey !!" <<endl;
                //i--;
            }
            pq2->pop();
        }
        delete pq2;
        cerr << "exited" <<endl;
    }


    void mesh::testHEDS(){
        int i =0;
        for(std::list<half_edge*>::iterator it = h_edges.begin();
            it != h_edges.end(); it++)
        {
            //std::cout << "Test evaluate "<< i++<<"  val= " << (*it)->evaluate() << std::endl;
            //std::cout << "Test contraction "<< i++<<"  val= " << *((*it)->getContraction()) << std::endl;
            //std::cout << "Test cw1 "<< i++<<"  val= " << (*it)->getVertex() << std::endl;
            //std::cout << "Test cw2 "<< i++<<"  val= " << (*it)->getOpposite().getVertex() << std::endl;
            //std::cout << "Test cw3 "<< i++<<"  val= " << (*it)->getCw().getVertex() << std::endl;
            //std::cout << "Test cw4 "<< i++<<"  val= " << (*it)->getCw().getOpposite().getVertex() << std::endl;
        }
    }

    const vector<v2>& mesh::get_texture() const
    {
        return v_texture;
    }
    vector<v2>& mesh::get_texture()
    {
        return v_texture;
    }

    vector<v3> mesh::get_normal_per_vertex() const
    {
        const vector<int>& c=v_connectivity;
        const vector<v3> normal_polygon=get_normal_per_polygon();

        //compute star
        map<int,list<int> > star;
        for(unsigned int k=0,N=c.size()/3;k<N;++k)
            for(unsigned int k_dim=0;k_dim<3;++k_dim)
                star[c[3*k+k_dim]].push_back(k);

        //compute per vertex normal
        vector<v3> normal_vertex;
        for(unsigned int k=0,N=v_vertices.size();k<N;++k)
        {
            v3 temp_normal;
            for(list<int>::const_iterator it=star[k].begin(),it_end=star[k].end();it!=it_end;++it)
                temp_normal += normal_polygon[*it];

            try
            {
                normal_vertex.push_back(temp_normal.normalized());
            }
            catch(proj::exception_proj e)
            {
                cout<<"Warning star degenerated"<<endl;
                normal_vertex.push_back(v3(0,0,1));
            }
        }

        return normal_vertex;

    }
    vector<v3> mesh::get_normal_per_polygon() const
    {
        const vector<v3>& v=v_vertices;
        const vector<int>& c=v_connectivity;

        //compute normal polygon
        vector<v3> normal_polygon;
        for(unsigned int k=0,N=c.size()/3;k<N;++k)
        {
            v3 x0=v[c[3*k+0]];v3 x1=v[c[3*k+1]];v3 x2=v[c[3*k+2]];

            try
            {
                normal_polygon.push_back( ((x1-x0).normalized().cross((x2-x0).normalized())).normalized());
            }
            catch(proj::exception_proj e)
            {
                cout<<"Warning degenerated polygon ["<<k<<"]"<<endl;
                normal_polygon.push_back(v3(0,0,1));
            }
        }

        return normal_polygon;
    }

    const v3& mesh::vertex_of_polygon(const unsigned int& index_polygon,const unsigned int& index_vertex) const
    {
        assert(index_vertex<3);

        unsigned int index=3*index_polygon+index_vertex;

        //check index
        if(index>=v_connectivity.size())
        {
            ostringstream msg;
            msg<<"Error index "<<index<<" outside bounds of size:"<<v_connectivity.size();
            throw proj::exception_mesh(msg.str(),__FILE__,__PRETTY_FUNCTION__,__LINE__);
        }
        //current index
        unsigned int u=v_connectivity[index];

        assert(u<v_vertices.size());

        //return index
        return v_vertices[u];
    }
    v3& mesh::vertex_of_polygon(const unsigned int& index_polygon,const unsigned int& index_vertex)
    {
        assert(index_vertex<3);

        unsigned int index=3*index_polygon+index_vertex;

        //check index
        if(index>=v_connectivity.size())
        {
            ostringstream msg;
            msg<<"Error index "<<index<<" outside bounds of size:"<<v_connectivity.size();
            throw proj::exception_mesh(msg.str(),__FILE__,__PRETTY_FUNCTION__,__LINE__);
        }
        //current index
        unsigned int u=v_connectivity[index];

        assert(u<v_vertices.size());

        //return index
        return v_vertices[u];
    }

    void mesh::normal_inversion()
    {
        const unsigned int N=v_normal.size();
        for(unsigned int k=0;k<N;++k)
            v_normal[k]*=-1.0;
    }

}


