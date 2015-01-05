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



#ifndef MATRIX4_HPP
#define MATRIX4_HPP

#include <iostream>
#include <vector>

#include <exception_proj.hpp>

namespace proj
{
class v3;
class v4;
class matrix3;

/** \brief Matrix 4x4 */
class matrix4
{


public:

    // ********************************************* //
    // ********************************************* //
    //  CONSTRUCTORS
    // ********************************************* //
    // ********************************************* //

    /** \brief empty constructor (identity) */
    matrix4();
    /** \brief direct constructor with every value */
    matrix4(const double& x00,const double& x01,const double& x02,const double& x03,
            const double& x10,const double& x11,const double& x12,const double& x13,
            const double& x20,const double& x21,const double& x22,const double& x23,
            const double& x30,const double& x31,const double& x32,const double& x33);
    /** \brief direct constructor from matrix 3 */
    matrix4(const matrix3& m);

    // ********************************************* //
    // ********************************************* //
    //  Special initialization
    // ********************************************* //
    // ********************************************* //

    /** \brief build identity matrix */
    static matrix4 identity();
    /** \brief build zero matrix */
    static matrix4 zeros();
    /** \brief build rotation matrix */
    static matrix4 rotation(const v3& axis,const double& angle);
    /** \brief build scaling matrix */
    static matrix4 scale(const double& s);
    /** \brief build scaling matrix */
    static matrix4 scale(const double& s_x,const double& s_y,const double& s_z,const double& s_w);
    /** \brief build translation matrix */
    static matrix4 translation(const v3& translation);
    /** \brief build from matrix3 and translation */
    static matrix4 transformation(const matrix3& m3,const v3& translation);

    // ********************************************* //
    // ********************************************* //
    //  Projection matrix (emulate glu(t) functions)
    // ********************************************* //
    // ********************************************* //

    /** \brief build a perspective projection similar to gluPerspective
        \param double fovy: in radian
         see: http://www.opengl.org/sdk/docs/man/xhtml/gluPerspective.xml
    */
    static matrix4 projection_perspective(const double& fovy,const double& aspect,const double& z_near,const double& z_far);
    /** \brief build a perspective projection (frustum) similar to gluPerspective
         see: http://www.opengl.org/sdk/docs/man/xhtml/glFrustum.xml
    */
    static matrix4 projection_frustum(const double& left,const double& right,const double& bottom,const double& top,const double& near,const double& far);
    /** \brief build an orthographic projection similar to gluPerspective
         see: http://www.opengl.org/sdk/docs/man/xhtml/glOrtho.xml
    */
    static matrix4 projection_orthographic(const double& left,const double& right,const double& bottom,const double& top,const double& near,const double& far);
    /** \brief build a perspective projection similar to gluLookAt
         see: http://www.opengl.org/sdk/docs/man/xhtml/gluLookAt.xml
    */
    static matrix4 projection_look_at(const matrix4& current_matrix,const v3& eye,const v3& center,const v3& up);


    // ********************************************* //
    // ********************************************* //
    //  Element access
    // ********************************************* //
    // ********************************************* //

    /** \brief Access to the k_th entry (k in [0,3]) */
    const double& operator()(const size_t& k1,const size_t& k2) const;
    /** \brief Access to the k_th entry (k in [0,3]) */
    double& operator()(const size_t& k1,const size_t& k2);

    /** \brief fast pointer access
            \warning unprotected access */
    const double* pointer() const;
    /** \brief fast pointer access
            \warning unprotected access */
    double* pointer_unprotected();



    // ********************************************* //
    // ********************************************* //
    //  Math operator
    // ********************************************* //
    // ********************************************* //

    /** \brief + operator */
    matrix4 operator+(const matrix4& m2) const;
    /** \brief + operator */
    matrix4 operator+(const double& s) const;

    /** \brief - operator */
    matrix4 operator-(const matrix4& m2) const;
    /** \brief - operator */
    matrix4 operator-(const double& s) const;


    /** \brief multiply by a scalar operator */
    matrix4 operator*(const double& s) const;
    /** \brief multiply matrix with a v4 */
    v4 operator*(const v4& v) const;
    /** \brief multiply matrix with a v3 (assume (v3.x,v3.y,v3.z,1) and normalize)*/
    v3 operator*(const v3& v) const;
    /** \brief matrix mulitplication */
    matrix4 operator*(const matrix4& m2) const;
    /** \brief divide by a scalar operator */
    matrix4 operator/(const double& s) const;


    /** \brief internal + */
    matrix4& operator+=(const matrix4& m);
    /** \brief internal + */
    matrix4& operator+=(const double& s);
    /** \brief internal - */
    matrix4& operator-=(const matrix4& m);
    /** \brief internal - */
    matrix4& operator-=(const double& s);
    /** \brief internal * */
    matrix4& operator*=(const double& s);
    /** \brief internal / */
    matrix4& operator/=(const double& s);

    /** \brief unary negation */
    matrix4 operator-() const;

    /** \brief does componentwise multiplication */
    matrix4 product_compontentwise(const matrix4& m) const;
    /** \brief does componentwise multiplication */
    matrix4& product_compontentwise_internal(const matrix4& m);

    /** \brief transpose matrix */
    matrix4 transposed() const;

    // ********************************************* //
    // ********************************************* //
    //  Deformation
    // ********************************************* //
    // ********************************************* //

    /** \brief Translated matrix (return of copy of the translated matrix) */
    matrix4 translated(const v3& translation) const;
    /** \brief Translated matrix (modify the matrix) */
    void translate_internal(const v3& translation);






    // ********************************************* //
    // ********************************************* //
    //  Projection matrix
    // ********************************************* //
    // ********************************************* //

    /** \brief convert 4x4 matrix into a 16 vector of double (glMultmatrixf) */
    std::vector<double> to_vector() const;

private:

    // ********************************************* //
    // ********************************************* //
    //  Internal parameters
    // ********************************************* //
    // ********************************************* //

    /** \brief internal storage of the matrix */
    double m[16];


    // ********************************************* //
    // ********************************************* //
    //  Helper
    // ********************************************* //
    // ********************************************* //

    /** \brief assert that a size_t belongs to [[0,3]] */
    void assert_size(const size_t& k1,const size_t& k2) const;

};

// ********************************************* //
// ********************************************* //
//  Output
// ********************************************* //
// ********************************************* //

/** \brief output the vector in ostream */
std::ostream& operator<<(std::ostream& stream,const matrix4& m);


/** \brief Special exception class for v3 */
class exception_matrix4 : public exception_proj
{
public:

    /** \brief empty constructor */
    exception_matrix4():exception_proj(){}
    /** \brief constructor with error information */
    exception_matrix4(const std::string& msg,const std::string& file,const std::string& caller,const int& line):exception_proj(msg,file,caller,line){}
};

/** \brief + operator */
matrix4 operator+(const double& s,const matrix4& m);
/** \brief - operator */
matrix4 operator-(const double& s,const matrix4& m);
/** \brief multiply by a scalar operator */
matrix4 operator*(const double& s,const matrix4& m);

}

#endif
