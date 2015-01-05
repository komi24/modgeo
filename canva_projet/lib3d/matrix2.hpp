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



#ifndef MATRIX2_HPP
#define MATRIX2_HPP

#include <iostream>
#include <vector>

#include <exception_proj.hpp>

namespace proj
{
class v2;


/** \brief Matrix 2x2 */
class matrix2
{

public:

    // ********************************************* //
    // ********************************************* //
    //  CONSTRUCTORS
    // ********************************************* //
    // ********************************************* //

    /** \brief empty constructor (identity) */
    matrix2();
    /** \brief direct constructor with every value */
    matrix2(const double& x00,const double& x01,
            const double& x10,const double& x11);

    // ********************************************* //
    // ********************************************* //
    //  Special initialization
    // ********************************************* //
    // ********************************************* //

    /** \brief build identity matrix */
    static matrix2 identity();
    /** \brief build zero matrix */
    static matrix2 zeros();
    /** \brief build rotation matrix */
    static matrix2 rotation(const double& angle);
    /** \brief build scaling matrix */
    static matrix2 scale(const double& s);
    /** \brief build scaling matrix */
    static matrix2 scale(const double& s_x,const double& s_y);


    // ********************************************* //
    // ********************************************* //
    //  Element access
    // ********************************************* //
    // ********************************************* //

    /** \brief Access to the k_th entry (k in [0,1]) */
    const double& operator()(const size_t& k1,const size_t& k2) const;
    /** \brief Access to the k_th entry (k in [0,1]) */
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
    matrix2 operator+(const matrix2& m2) const;
    /** \brief + operator */
    matrix2 operator+(const double& s) const;

    /** \brief - operator */
    matrix2 operator-(const matrix2& m2) const;
    /** \brief - operator */
    matrix2 operator-(const double& s) const;


    /** \brief multiply by a scalar operator */
    matrix2 operator*(const double& s) const;
    /** \brief multiply matrix with a v3 */
    v2 operator*(const v2& v) const;
    /** \brief matrix mulitplication */
    matrix2 operator*(const matrix2& m2) const;
    /** \brief divide by a scalar operator */
    matrix2 operator/(const double& s) const;


    /** \brief internal + */
    matrix2& operator+=(const matrix2& m);
    /** \brief internal + */
    matrix2& operator+=(const double& s);
    /** \brief internal - */
    matrix2& operator-=(const matrix2& m);
    /** \brief internal - */
    matrix2& operator-=(const double& s);
    /** \brief internal * */
    matrix2& operator*=(const double& s);
    /** \brief internal / */
    matrix2& operator/=(const double& s);

    /** \brief unary negation */
    matrix2 operator-() const;

    /** \brief does componentwise multiplication */
    matrix2 product_compontentwise(const matrix2& m) const;
    /** \brief does componentwise multiplication */
    matrix2& product_compontentwise_internal(const matrix2& m);

    /** \brief transpose matrix */
    matrix2 transposed() const;







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
    double m[4];


    // ********************************************* //
    // ********************************************* //
    //  Helper
    // ********************************************* //
    // ********************************************* //

    /** \brief assert that a size_t belongs to [[0,1]] */
    void assert_size(const size_t& k1,const size_t& k2) const;

};

/** \brief + operator */
matrix2 operator+(const double& s,const matrix2& m);
/** \brief - operator */
matrix2 operator-(const double& s,const matrix2& m);
/** \brief multiply by a scalar operator */
matrix2 operator*(const double& s,const matrix2& m);

// ********************************************* //
// ********************************************* //
//  Output
// ********************************************* //
// ********************************************* //

/** \brief output the vector in ostream */
std::ostream& operator<<(std::ostream& stream,const matrix2& m);



/** \brief Special exception class for v3 */
class exception_matrix2 : public exception_proj
{
public:

    /** \brief empty constructor */
    exception_matrix2():exception_proj(){}
    /** \brief constructor with error information */
    exception_matrix2(const std::string& msg,const std::string& file,const std::string& caller,const int& line):exception_proj(msg,file,caller,line){}
};



}

#endif
