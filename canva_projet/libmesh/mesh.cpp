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

//TODO #include <half_edge.hpp>

using namespace std;

namespace proj
{

    mesh::mesh(){
        //half_edge h(this);
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
    bounded_priority_queue<vertexpair> mesh::selection(){
        bounded_priority_queue<vertexpair> pq(10);

        for (size_t i = 0; i < 500; ++i) {//v_vertices.size(); ++i) {
            for (size_t j = 0; j < 500; ++j) {//v_vertices.size(); ++j) {
                if(i != j) {
                    vertexpair auxpair(i, j, euclideanLength(v_vertices[i], v_vertices[j]));
                    pq.push(auxpair);
                }
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
    vector<int> mesh::updateTables(vector<int> v, int m, int n)
    {
        v_vertices.erase(v_vertices.begin() + m); // en el 5889 peta
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
                else
                    cout << "Error in connectivity table!!!" << endl;
            } else {
                // Only one vertex will change, we will take care of it after
            }
        }

        // We erase the faces
        if(indexToDelete1 != -1) {
            v.erase(v.begin()+indexToDelete1,v.begin()+indexToDelete1+3);

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

    void mesh::simplification() {
        cout << "Size of vertices: " << v_vertices.size() << endl;
        cout << "Size of normals: " << v_normal.size() << endl;
        cout << "Size of connectivity: " << v_connectivity.size() << endl;
        cout << "\n";

        bounded_priority_queue<vertexpair> pq = selection();
        pq.pop_all();

        for(size_t i=0;i<1;++i) {
            //priority_queue<vertexpair> paux = pq.pop_all();
            //vertexpair vertexToDelete = pq.pop();
            //v_connectivity = updateTables(v_connectivity, vertexToDelete.vert1, vertexToDelete.vert2);
            //pq.pop();
        }

        cout << "Size of vertices: " << v_vertices.size() << endl;
        cout << "Size of normals: " << v_normal.size() << endl;
        cout << "Size of connectivity: " << v_connectivity.size() << endl;
        cout << "\n";
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

        std::cout << std::endl << "todoList.front()" << std::endl;
        //TODO ERASE for(std::deque<int>::iterator ite = todoList.begin(); ite!=todoList.end(); ite++)
        //    std::cout << *ite << std::endl;

        //start with one triangle tranfered to the HE list /processing queue (boundary)
        for(int i=0; i<3; i++) {
            p[i]=todoList.front();
            todoList.pop_front();
        }
        curr = new facet(p[0],p[1],p[2]);
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
        std::cout << std::endl << "todoList.front()" << std::endl;
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
                p[2]=*buf[3-found1-found2];
                //TODO ERASE std::cout << endl << "TAILLE ok1 = " << todoList.size() << endl;
                //std::cout << "TAILLE ok1 = " << h_edges.size() << endl;
                //std::cout << "TAILLE ok1 = " << boundary.size() << endl;
                //std::cout << " p[0] " << p[0] << " p[1] " << p[1] << " p[2] " << p[2] << endl;
                //for(std::deque<half_edge*>::iterator ite = boundary.begin(); ite!=boundary.end(); ite++)
                //    std::cout << (*ite)->getVertex() << "  " << (*ite)->getOpposite().getVertex() << std::endl;
                //Link inner HE and outter HE
                curr = new facet(p[0],p[1],p[2]);
                //create  2 inner HE and 2 outter HE and link opposites
                //and push_back outter HE in boundary
                for(int i=1; i<3; i++){
                    he[i] = new half_edge(p[i],curr);
                    he[i+3] = new half_edge(p[(i+1)%3]);
                    he[i]->setOpposite(he[i+3]);
                    he[i+3]->setOpposite(he[i]);
                    boundary.push_back(he[i+3]);
                    h_edges.push_back(he[i]);
                }
                h_edges.push_back(he[0]);
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
                //std::cout << "TAILLE ok = " << h_edges.size() << endl;
                //std::cout << " p[0] " << he[0]->getVertex() << " p[1] " << he[0]->getOpposite().getVertex() << endl;
                //for(std::deque<half_edge*>::iterator ite = boundary.begin(); ite!=boundary.end(); ite++)
                //    std::cout << (*ite)->getVertex() << "  " << (*ite)->getOpposite().getVertex() << std::endl;

                //check if some outter HE can be opposite-linked to existing HE
                std::deque<half_edge*>::iterator it1 = boundary.begin();
                half_edge h1 = *(*it1);
                half_edge h2 = h1.getOpposite();
                half_edge h3 = he[0]->getOpposite();
                while(((h1.getVertex()!=h3.getVertex())
                      ||(h2.getVertex()!=he[0]->getVertex()))
                      &&(it1 != boundary.end())){
                    it1++;
                    h1 = *(*it1);
                    h2 = h1.getOpposite();
                }
                if((h1.getVertex()==h3.getVertex())
                        &&(h2.getVertex()==he[0]->getVertex())){
                    //delete both outters HE and link inners HE
                    delete *it1;
                    boundary.erase(it1);
                    delete he[0];
                    h3.setOpposite(&h2);
                    h2.setOpposite(&h3);
                }else{
                    delete he[0];
                }
            }
            //size of boundary --1 / Enlever le premier terme
            boundary.pop_front();
        }
        //TODO ERASE for(std::list<half_edge*>::iterator ite = h_edges.begin(); ite!=h_edges.end(); ite++)
        //    std::cout << (*ite)->getVertex() << "  " << (*ite)->getOpposite().getVertex() << std::endl;

    }

    void mesh::testHEDS(){
        for(std::list<half_edge*>::iterator it = h_edges.begin();
            it != h_edges.end(); it++)
        {
            std::cout << "Test 1 " << (*it)->evaluate() << std::endl;
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


