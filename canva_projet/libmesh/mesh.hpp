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


#ifndef MESH_HPP
#define MESH_HPP

#include <exception_proj.hpp>
#include <v3.hpp>
#include <v2.hpp>
#include <vector>
#include <string>



namespace proj
{
class matrix3;

/** \brief Container class for a generic mesh with normal, color, texture, ... */
class mesh
{
    public:


        // ********************************************* //
        // ********************************************* //
        //  Access data
        // ********************************************* //
        // ********************************************* //

        /** \brief Accessor to the vertex value */
        const v3& vertex(const unsigned int& index) const;
        /** \brief Accessor to the vertex value */
        v3& vertex(const unsigned int& index);

        /** \brief Accessor to the vertex value */
        const v3& vertex_of_polygon(const unsigned int& index_polygon,const unsigned int& index_vertex) const;
        /** \brief Accessor to the vertex value */
        v3& vertex_of_polygon(const unsigned int& index_polygon,const unsigned int& index_vertex);

        /** \brief Accessor to the normal value */
        const v3& normal(const unsigned int& index) const;
        /** \brief Accessor to the normal value */
        v3& normal(const unsigned int& index);

        /** \brief Accessor to the color value */
        const v3& color(const unsigned int& index) const;
        /** \brief Accessor to the color value */
        v3& color(const unsigned int& index);

        /** \brief Accessor to the connectivity value */
        const int& connectivity(const unsigned int& index) const;
        /** \brief Accessor to the connectivity value */
        int& connectivity(const unsigned int& index);

        /** \brief Accessor to the uv-texture value */
        const v2& texture(const unsigned int& index) const;
        /** \brief Accessor to the uv-texture value */
        v2& texture(const unsigned int& index);

        /** \brief return internal vertices vector */
        const std::vector<v3>& get_vertices() const;
        /** \brief return internal normal vector */
        const std::vector<v3>& get_normal() const;
        /** \brief return internal color vector */
        const std::vector<v3>& get_color() const;
        /** \brief return internal connectivity vector */
        const std::vector<int>& get_connectivity() const;
        /** \brief return internal uv texture vector */
        const std::vector<v2>& get_texture() const;

        /** \brief return internal vertices vector */
        std::vector<v3>& get_vertices();
        /** \brief return internal normal vector */
        std::vector<v3>& get_normal();
        /** \brief return internal color vector */
        std::vector<v3>& get_color();
        /** \brief return internal connectivity vector */
        std::vector<int>& get_connectivity();
        /** \brief return internal uv texture vector */
        std::vector<v2>& get_texture();


        /** \brief Add a vertex to the mesh */
        void add_vertex(const v3& vertex_to_add);
        /** \brief Add a texture to the mesh */
        void add_texture(const v2& texture_to_add);
        /** \brief Add a triangle to the mesh */
        void add_triangle(const int u0,const int u1,const int u2);


        // ********************************************* //
        // ********************************************* //
        //  Size
        // ********************************************* //
        // ********************************************* //

        /** \brief get the number of triangle */
        unsigned int number_of_triangle() const;

        /** \brief get the number of vertices */
        unsigned int number_of_vertices() const;

        // ********************************************* //
        // ********************************************* //
        //  Color
        // ********************************************* //
        // ********************************************* //

        /** \brief fill mesh with constant color */
        void fill_color(const v3& c);
        /** \brief fill mesh with color depending of (x,y,z)-coordinates */
        void fill_color_xyz();
        /** \brief fill mesh with color depending of normal orientation */
        void fill_color_normal();


        // ********************************************* //
        // ********************************************* //
        //  Normal
        // ********************************************* //
        // ********************************************* //

        /** \brief Compute a per-vertex normal and fill the internal vector */
        void compute_normal();

        /** \brief Inverse the direction of the normal */
        void normal_inversion();

        /** \brief get the vector per vertex */
        std::vector<v3> get_normal_per_vertex() const;
        /** \brief get the vector per polygon */
        std::vector<v3> get_normal_per_polygon() const;

        // ********************************************* //
        // ********************************************* //
        //  Math Operators
        // ********************************************* //
        // ********************************************* //

        /** \brief translation */
        friend mesh operator+(const v3& x,const mesh& m);
        /** \brief translation */
        friend mesh operator+(const mesh& m,const v3& x);
        /** \brief internal translation */
        mesh& operator+=(const v3& x);

        /** \brief translation */
        friend mesh operator-(const mesh& m,const v3& x);
        /** \brief internal translation */
        mesh& operator-=(const v3& x);

        /** \brief uniform scaling */
        friend mesh operator*(const double& s,const mesh& m);
        /** \brief uniform scaling */
        friend mesh operator*(const mesh& m,const double& s);
        /** \brief uniform scaling */
        mesh& operator*=(const double& s);


        /** \brief scale the mesh with anisotropical values */
        void scale(const double& sx,const double& sy,const double& sz);
        /** \brief Set vertices to fit in scalex[-1,1]x[-1,1].

            z-coordinate is set to start at -1
            Auto fit the unit square ((-1,-1,1),(-1,1,1),(1,-1,1),(1,1,1))
        */
        void auto_scale(const double& scale=1.0);

        /** \brief Apply matrix to every vertices */
        void apply(const proj::matrix3 R);


        // ********************************************* //
        // ********************************************* //
        //  I/O
        // ********************************************* //
        // ********************************************* //

        /** \brief load a off file */
        void load_file(const std::string &filename);

    private:

        // ********************************************* //
        // ********************************************* //
        //  Internal data
        // ********************************************* //
        // ********************************************* //

        /** \brief internal vertices storage */
        std::vector<v3> v_vertices;
        /** \brief internal normal storage */
        std::vector<v3> v_normal;
        /** \brief internal color storage */
        std::vector<v3> v_color;
        /** \brief internal texture coordinate storage */
        std::vector<v2> v_texture;

        /** \brief internal connectivity storage */
        std::vector<int> v_connectivity;

};



/** \brief Special exception class for image */
class exception_mesh : public exception_proj
{
    public:

        /** \brief empty constructor */
        exception_mesh():exception_proj(){}
        /** \brief constructor with error information */
        exception_mesh(const std::string& msg,const std::string& file,const std::string& caller,const int& line):exception_proj(msg,file,caller,line){}
};
}

#endif
