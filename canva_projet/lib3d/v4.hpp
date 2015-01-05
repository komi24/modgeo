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



#ifndef V4_HPP
#define V4_HPP

#include <string>
#include <iostream>

#include <exception_proj.hpp>

namespace proj
{
class v3;
class v2;

/** \brief Vectors/Points 4D */
class v4
{
public:

    // ********************************************* //
    // ********************************************* //
    //  CONSTRUCTORS
    // ********************************************* //
    // ********************************************* //

    /** \brief empty constructor */
    v4();
    /** \brief direct constructor */
    v4(const double& x,const double& y,const double& z,const double& w);

    // ********************************************* //
    // ********************************************* //
    //  Get/set
    // ********************************************* //
    // ********************************************* //

    /** \brief get x coordinate */
    const double& x() const;
    /** \brief get x coordinate */
    double& x();
    /** \brief get y coordinate */
    const double& y() const;
    /** \brief get y coordinate */
    double& y();
    /** \brief get z coordinate */
    const double& z() const;
    /** \brief get z coordinate */
    double& z();
    /** \brief get w coordinate */
    const double& w() const;
    /** \brief get w coordinate */
    double& w();

    /** \brief Access to the k_th entry (k in [0,3]) */
    const double& operator[](const size_t& k) const;
    /** \brief Access to the k_th entry (k in [0,3]) */
    double& operator[](const size_t& k);
    /** \brief Access to the k_th entry (k in [0,3]) */
    const double& operator()(const size_t& k) const;
    /** \brief Access to the k_th entry (k in [0,3]) */
    double& operator()(const size_t& k);

    /** \brief set every entry to 0 */
    void set_zero();

    /** \brief fast pointer access
        \warning unprotected access */
    const double *pointer() const;

    // ********************************************* //
    // ********************************************* //
    //  Convert to lower dimension
    // ********************************************* //
    // ********************************************* //

    /** \brief convert to v3 (x,y,z) */
    v3 to_v3() const;
    /** \brief convert to v2 (x,y) */
    v2 to_v2() const;



    // ********************************************* //
    // ********************************************* //
    //  Math operation
    // ********************************************* //
    // ********************************************* //

    /** \brief perform dot product between two v4 */
    double dot(const v4& p) const;

    /** \brief get the norm of the vector */
    double norm() const;
    /** \brief get the square norm of the vector */
    double norm2() const;
    /** \brief normalize the vector to unit length */
    v4 normalized() const;






    // ********************************************* //
    // ********************************************* //
    //  Operator +-*/
    // ********************************************* //
    // ********************************************* //

    /** \brief + operator */
    v4 operator+(const v4& p2) const;
    /** \brief + operator */
    v4 operator+(const double& s) const;

    /** \brief - operator */
    v4 operator-(const v4& p2) const;
    /** \brief - operator */
    v4 operator-(const double& s) const;

    /** \brief multiply by a scalar operator */
    v4 operator*(const double& s) const;
    /** \brief divide by a scalar operator */
    v4 operator/(const double& s) const;

    /** \brief internal + */
    v4& operator+=(const v4& p);
    /** \brief internal + */
    v4& operator+=(const double& s);
    /** \brief internal - */
    v4& operator-=(const v4& p);
    /** \brief internal - */
    v4& operator-=(const double& s);
    /** \brief internal * */
    v4& operator*=(const double& s);
    /** \brief internal / */
    v4& operator/=(const double& s);

    /** \brief unary negation */
    v4 operator-() const;

    /** \brief does componentwise mutliplication
            \return MC_v2d(x*p.x(),y*p.y(),z*p.z())
        */
    v4 product_compontentwise(const v4& p) const;
    /** \brief does componentwise mutliplication

            perform p=(p.x()*p2.x(),p.y()*p2.x())
        */
    v4& product_compontentwise_internal(const v4& p);
    /** \brief internal scaling (similar to componentwise) */
    void scale(const double& sx,const double& sy,const double& sz,const double& sw);


    // ********************************************* //
    // ********************************************* //
    //  Output
    // ********************************************* //
    // ********************************************* //

    /** \brief export the value as string cout<<v4(2,3,6,7) => 2 3 6 7 */
    std::string to_string() const;



private:


    // ********************************************* //
    // ********************************************* //
    //  Internal parameters
    // ********************************************* //
    // ********************************************* //

    /** \brief x coordinate */
    double internal_x;
    /** \brief y coordinate */
    double internal_y;
    /** \brief z coordinate */
    double internal_z;
    /** \brief w coordinate */
    double internal_w;


    // ********************************************* //
    // ********************************************* //
    //  Helper
    // ********************************************* //
    // ********************************************* //

    /** \brief assert that a size_t belongs to [[0,2]] */
    void assert_size(const size_t& k) const;

};

/** \brief + operator */
v4 operator+(const double& s,const v4& p);
/** \brief - operator */
v4 operator-(const double& s,const v4& p);
/** \brief multiply by a scalar operator */
v4 operator*(const double& s,const v4& p);

// ********************************************* //
// ********************************************* //
//  Output
// ********************************************* //
// ********************************************* //

/** \brief output the vector in ostream as (x,y,z) */
std::ostream& operator<<(std::ostream& stream,const v4& p);

/** \brief Special exception class for v4 */
class exception_v4 : public exception_proj
{
public:

    /** \brief empty constructor */
    exception_v4():exception_proj(){}
    /** \brief constructor with error information */
    exception_v4(const std::string& msg,const std::string& file,const std::string& caller,const int& line):exception_proj(msg,file,caller,line){}
};

}



#endif
