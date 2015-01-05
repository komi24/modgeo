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



#ifndef MATRIX3_HPP
#define MATRIX3_HPP

#include <iostream>
#include <vector>

#include <exception_proj.hpp>

namespace proj
{
class v3;


/** \brief Matrix 3x3 */
class matrix3
{

public:

    // ********************************************* //
    // ********************************************* //
    //  CONSTRUCTORS
    // ********************************************* //
    // ********************************************* //

    /** \brief empty constructor (identity) */
    matrix3();
    /** \brief direct constructor with every value */
    matrix3(const double& x00,const double& x01,const double& x02,
            const double& x10,const double& x11,const double& x12,
            const double& x20,const double& x21,const double& x22);

    // ********************************************* //
    // ********************************************* //
    //  Special initialization
    // ********************************************* //
    // ********************************************* //

    /** \brief build identity matrix */
    static matrix3 identity();
    /** \brief build zero matrix */
    static matrix3 zeros();
    /** \brief build rotation matrix */
    static matrix3 rotation(const v3& axis,const double& angle);
    /** \brief build scaling matrix */
    static matrix3 scale(const double& s);
    /** \brief build scaling matrix */
    static matrix3 scale(const double& s_x,const double& s_y,const double& s_z);


    // ********************************************* //
    // ********************************************* //
    //  Element access
    // ********************************************* //
    // ********************************************* //

    /** \brief Access to the k_th entry (k in [0,2]) */
    const double& operator()(const size_t& k1,const size_t& k2) const;
    /** \brief Access to the k_th entry (k in [0,2]) */
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
    matrix3 operator+(const matrix3& m2) const;
    /** \brief + operator */
    matrix3 operator+(const double& s) const;

    /** \brief - operator */
    matrix3 operator-(const matrix3& m2) const;
    /** \brief - operator */
    matrix3 operator-(const double& s) const;


    /** \brief multiply by a scalar operator */
    matrix3 operator*(const double& s) const;
    /** \brief multiply matrix with a v3 */
    v3 operator*(const v3& v) const;
    /** \brief matrix mulitplication */
    matrix3 operator*(const matrix3& m2) const;
    /** \brief divide by a scalar operator */
    matrix3 operator/(const double& s) const;


    /** \brief internal + */
    matrix3& operator+=(const matrix3& m);
    /** \brief internal + */
    matrix3& operator+=(const double& s);
    /** \brief internal - */
    matrix3& operator-=(const matrix3& m);
    /** \brief internal - */
    matrix3& operator-=(const double& s);
    /** \brief internal * */
    matrix3& operator*=(const double& s);
    /** \brief internal / */
    matrix3& operator/=(const double& s);

    /** \brief unary negation */
    matrix3 operator-() const;

    /** \brief does componentwise multiplication  */
    matrix3 product_compontentwise(const matrix3& m) const;
    /** \brief does componentwise multiplication  */
    matrix3& product_compontentwise_internal(const matrix3& m);

    /** \brief transpose matrix */
    matrix3 transposed() const;



    // ********************************************* //
    // ********************************************* //
    //  Projection matrix
    // ********************************************* //
    // ********************************************* //

    /** \brief convert 3x3 matrix into a vector of double of size 9 */
    std::vector<double> to_vector() const;

private:

    // ********************************************* //
    // ********************************************* //
    //  Internal parameters
    // ********************************************* //
    // ********************************************* //

    /** \brief internal storage of the matrix */
    double m[9];


    // ********************************************* //
    // ********************************************* //
    //  Helper
    // ********************************************* //
    // ********************************************* //

    /** \brief assert that a size_t belongs to [[0,2]] */
    void assert_size(const size_t& k1,const size_t& k2) const;

};

/** \brief + operator */
matrix3 operator+(const double& s,const matrix3& m);
/** \brief - operator */
matrix3 operator-(const double& s,const matrix3& m);
/** \brief multiply by a scalar operator */
matrix3 operator*(const double& s,const matrix3& m);

// ********************************************* //
// ********************************************* //
//  Output
// ********************************************* //
// ********************************************* //

/** \brief output the vector in ostream */
std::ostream& operator<<(std::ostream& stream,const matrix3& m);

/** \brief Special exception class for v3 */
class exception_matrix3 : public exception_proj
{
public:

    /** \brief empty constructor */
    exception_matrix3():exception_proj(){}
    /** \brief constructor with error information */
    exception_matrix3(const std::string& msg,const std::string& file,const std::string& caller,const int& line):exception_proj(msg,file,caller,line){}
};



}

#endif
