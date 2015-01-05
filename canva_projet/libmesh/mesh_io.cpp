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



#include <mesh_io.hpp>

#include <mesh.hpp>

#include <iostream>
#include <fstream>
#include <sstream>


namespace proj
{
mesh mesh_io::load_off_file(const std::string& filename)
{
    mesh m;

    std::vector<v3> v_vertices;
    std::vector<int> v_connectivity;

    std::ifstream fid(filename.c_str());
    if(!fid.good())
        throw exception_mesh("Cannot open file "+filename,__FILE__,__FUNCTION__,__LINE__);

    std::string buffer;

    //find OFF header
    bool find_off=false;
    while(find_off==false)
    {
        if(!fid.good())
            throw exception_mesh("Cannot find OFF header in file "+filename,__FILE__,__FUNCTION__,__LINE__);
        std::getline(fid,buffer);
        if(buffer.find("OFF")!=std::string::npos)
            find_off=true;
    }

    //read number of vertices + triangles
    int N_vertex=0,N_triangle=0;
    std::getline(fid,buffer);
    std::stringstream tokens(buffer);
    tokens>>N_vertex>>N_triangle;


    //read vertices
    for(int k=0;k<N_vertex;++k)
    {
        std::getline(fid,buffer);
        if(buffer.size()>0 && buffer[0]=='#') {--k; continue;}

        v3 p;
        std::stringstream tokens_vertices(buffer);
        tokens_vertices>>p.x()>>p.y()>>p.z();

        v_vertices.push_back(p);
    }

    //read connectivity
    for(int k=0;k<N_triangle;++k)
    {
        std::getline(fid,buffer);
        if(buffer.size()>0 && buffer[0]=='#') {--k; continue;}

        int N_size,u0,u1,u2;
        std::stringstream tokens_connectivity(buffer);
        tokens_connectivity>>N_size>>u0>>u1>>u2;


        if(N_size!=3)
            throw exception_mesh("Cannot read OFF with non triangular faces for file "+filename,__FILE__,__FUNCTION__,__LINE__);

        v_connectivity.push_back(u0);v_connectivity.push_back(u1);v_connectivity.push_back(u2);
    }

    fid.close();

    m.get_connectivity()=v_connectivity;
    m.get_vertices()=v_vertices;
    return m;

}

mesh mesh_io::load_obj_file(const std::string& filename)
{
    mesh m;


    std::ifstream fid(filename.c_str());
    if(!fid.good())
        throw exception_mesh("Cannot open file "+filename,__FILE__,__FUNCTION__,__LINE__);

    std::string buffer;

    //read the whole file
    while(fid.good()==true)
    {
        //read line
        std::getline(fid,buffer);

        if(buffer.size()>0)
        {
            std::stringstream tokens_buffer(buffer);
            std::string first_word;
            tokens_buffer>>first_word;

            //vertices
            if(first_word=="v")
            {
                v3 vertex;
                tokens_buffer>>vertex.x();
                tokens_buffer>>vertex.y();
                tokens_buffer>>vertex.z();

                m.add_vertex(vertex);
            }

            //texture
            if(first_word=="vt")
            {
                v2 texture;
                tokens_buffer>>texture.x();
                tokens_buffer>>texture.y();

                m.add_texture(texture);
            }

            //connectivity
            if(first_word=="f")
            {
                int u0=0,u1=0,u2=0;
                tokens_buffer>>u0;
                tokens_buffer>>u1;
                tokens_buffer>>u2;

                m.add_triangle(u0-1,u1-1,u2-1);

            }

        }

    }

//    //read number of vertices + triangles
//    int N_vertex=0,N_triangle=0;
//    std::getline(fid,buffer);
//    std::stringstream tokens(buffer);
//    tokens>>N_vertex>>N_triangle;


//    //read vertices
//    for(int k=0;k<N_vertex;++k)
//    {
//        std::getline(fid,buffer);
//        if(buffer.size()>0 && buffer[0]=='#') {--k; continue;}

//        v3 p;
//        std::stringstream tokens_vertices(buffer);
//        tokens_vertices>>p.x()>>p.y()>>p.z();

//        v_vertices.push_back(p);
//    }

//    //read connectivity
//    for(int k=0;k<N_triangle;++k)
//    {
//        std::getline(fid,buffer);
//        if(buffer.size()>0 && buffer[0]=='#') {--k; continue;}

//        int N_size,u0,u1,u2;
//        std::stringstream tokens_connectivity(buffer);
//        tokens_connectivity>>N_size>>u0>>u1>>u2;


//        if(N_size!=3)
//            throw exception_mesh("Cannot read OFF with non triangular faces for file "+filename,__FILE__,__FUNCTION__,__LINE__);

//        v_connectivity.push_back(u0);v_connectivity.push_back(u1);v_connectivity.push_back(u2);
//    }

//    fid.close();

    //m.get_connectivity()=v_connectivity;
   // m.get_vertices()=v_vertices;
    return m;

}
}
