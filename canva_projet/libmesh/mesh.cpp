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

namespace proj
{

    const std::vector<v3>& mesh::get_vertices() const{return v_vertices;}
    const std::vector<v3>& mesh::get_normal() const{return v_normal;}
    const std::vector<v3>& mesh::get_color() const{return v_color;}
    /** TODO  update the connectivity with half edge structure if needed */
    const std::vector<int>& mesh::get_connectivity() const{return v_connectivity;}

    std::vector<v3>& mesh::get_vertices() {return v_vertices;}
    std::vector<v3>& mesh::get_normal() {return v_normal;}
    std::vector<v3>& mesh::get_color() {return v_color;}
    std::vector<int>& mesh::get_connectivity() {return v_connectivity;}

    void mesh::load_file(const std::string &filename)
    {
        if(filename.find(".off")!=std::string::npos)
            *this=mesh_io::load_off_file(filename);
        else if(filename.find(".obj")!=std::string::npos)
            *this=mesh_io::load_obj_file(filename);
        else
        {
            std::stringstream msg;
            msg<<"Error, file format unknown ["<<filename<<"]";
            proj::exception_proj(msg.str(),__FILE__,__FUNCTION__,__LINE__);
        }
    }

    // Complexity: O(numVertices)
    std::vector<v3> updateVertices(std::vector<v3> vertices, int n)
    {
        std::vector<v3> result;
        for (std::size_t i=0;i<vertices.size();++i) {
            if(i != n) result.push_back(vertices[i]);
        }
        return result;
    }

    mesh& mesh::simplification()
    {
        /** EL MANEJO DE LA TABLA VERTICES FUNCIONA BIEN */
        std::vector<v3> vertices = v_vertices;
        std::vector<int> connectivity = v_connectivity;

        int vertexToDelete = -1;
        int numOriginalVertices = vertices.size();

        for(std::size_t i=0;i<numOriginalVertices;++i)
        {
            vertexToDelete = rand() % vertices.size();
            vertices = updateVertices(vertices, vertexToDelete);
            //connectivity = updateConnectivity(connectivity, vertexToDelete);
        }

    }






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
        double s=std::max(u.x(),u.y());

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
             v_color[k]=v3(std::fabs(n.x()),std::fabs(n.y()),std::fabs(n.z()));
         }
    }

    const v3& mesh::vertex(const unsigned int& index) const
    {
        //check index
        if(index>=v_vertices.size())
        {
            std::ostringstream msg;
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
            std::ostringstream msg;
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
            std::ostringstream msg;
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
            std::ostringstream msg;
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
            std::ostringstream msg;
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
            std::ostringstream msg;
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
            std::ostringstream msg;
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
            std::ostringstream msg;
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
            std::ostringstream msg;
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
            std::ostringstream msg;
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

    const std::vector<v2>& mesh::get_texture() const
    {
        return v_texture;
    }
    std::vector<v2>& mesh::get_texture()
    {
        return v_texture;
    }

    std::vector<v3> mesh::get_normal_per_vertex() const
    {
        const std::vector<int>& c=v_connectivity;
        const std::vector<v3> normal_polygon=get_normal_per_polygon();

        //compute star
        std::map<int,std::list<int> > star;
        for(unsigned int k=0,N=c.size()/3;k<N;++k)
            for(unsigned int k_dim=0;k_dim<3;++k_dim)
                star[c[3*k+k_dim]].push_back(k);

        //compute per vertex normal
        std::vector<v3> normal_vertex;
        for(unsigned int k=0,N=v_vertices.size();k<N;++k)
        {
            v3 temp_normal;
            for(std::list<int>::const_iterator it=star[k].begin(),it_end=star[k].end();it!=it_end;++it)
                temp_normal += normal_polygon[*it];

            try
            {
                normal_vertex.push_back(temp_normal.normalized());
            }
            catch(proj::exception_proj e)
            {
                std::cout<<"Warning star degenerated"<<std::endl;
                normal_vertex.push_back(v3(0,0,1));
            }
        }

        return normal_vertex;

    }
    std::vector<v3> mesh::get_normal_per_polygon() const
    {
        const std::vector<v3>& v=v_vertices;
        const std::vector<int>& c=v_connectivity;

        //compute normal polygon
        std::vector<v3> normal_polygon;
        for(unsigned int k=0,N=c.size()/3;k<N;++k)
        {
            v3 x0=v[c[3*k+0]];v3 x1=v[c[3*k+1]];v3 x2=v[c[3*k+2]];

            try
            {
                normal_polygon.push_back( ((x1-x0).normalized().cross((x2-x0).normalized())).normalized());
            }
            catch(proj::exception_proj e)
            {
                std::cout<<"Warning degenerated polygon ["<<k<<"]"<<std::endl;
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
            std::ostringstream msg;
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
            std::ostringstream msg;
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


