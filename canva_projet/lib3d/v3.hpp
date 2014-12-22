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



#ifndef V3_HPP
#define V3_HPP

#include <string>
#include <iostream>

#include <exception_proj.hpp>

namespace proj
{
class v2;

/** \brief Vectors/Points 3D */
class v3
{
public:

    // ********************************************* //
    // ********************************************* //
    //  CONSTRUCTORS
    // ********************************************* //
    // ********************************************* //

    /** \brief empty constructor */
    v3();
    /** \brief direct constructor */
    v3(const double& x,const double& y,const double& z);

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

    /** \brief Access to the k_th entry (k in [0,2]) */
    const double& operator[](const size_t& k) const;
    /** \brief Access to the k_th entry (k in [0,2]) */
    double& operator[](const size_t& k);
    /** \brief Access to the k_th entry (k in [0,2]) */
    const double& operator()(const size_t& k) const;
    /** \brief Access to the k_th entry (k in [0,2]) */
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

    /** \brief convert to v2 (x,y) */
    v2 to_v2() const;


    // ********************************************* //
    // ********************************************* //
    //  Math operation
    // ********************************************* //
    // ********************************************* //

    /** \brief perform dot product between two v3 */
    double dot(const v3& p) const;

    /** \brief get the norm of the vector */
    double norm() const;
    /** \brief get the square norm of the vector */
    double norm2() const;
    /** \brief normalize the vector to unit length */
    v3 normalized() const;

    /** \brief compute cross product with an other vector */
    v3 cross(const v3& p) const;




    // ********************************************* //
    // ********************************************* //
    //  Operator +-*/
    // ********************************************* //
    // ********************************************* //

    /** \brief + operator */
    v3 operator+(const v3& p2) const;
    /** \brief + operator */
    v3 operator+(const double& s) const;

    /** \brief - operator */
    v3 operator-(const v3& p2) const;
    /** \brief - operator */
    v3 operator-(const double& s) const;


    /** \brief multiply by a scalar operator */
    v3 operator*(const double& s) const;
    /** \brief divide by a scalar operator */
    v3 operator/(const double& s) const;

    /** \brief internal + */
    v3& operator+=(const v3& p);
    /** \brief internal + */
    v3& operator+=(const double& s);
    /** \brief internal - */
    v3& operator-=(const v3& p);
    /** \brief internal - */
    v3& operator-=(const double& s);
    /** \brief internal * */
    v3& operator*=(const double& s);
    /** \brief internal / */
    v3& operator/=(const double& s);

    /** \brief unary negation */
    v3 operator-() const;

    /** \brief does componentwise mutliplication
            \return MC_v2d(x*p.x(),y*p.y(),z*p.z())
        */
    v3 product_compontentwise(const v3& p) const;
    /** \brief does componentwise mutliplication

            perform p=(p.x()*p2.x(),p.y()*p2.x())
        */
    v3& product_compontentwise_internal(const v3& p);
    /** \brief internal scaling (similar to componentwise) */
    void scale(const double& sx,const double& sy,const double& sz);


    // ********************************************* //
    // ********************************************* //
    //  Output
    // ********************************************* //
    // ********************************************* //

    /** \brief export the value as string cout<<v3(2,3,6) => 2 3 6 */
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


    // ********************************************* //
    // ********************************************* //
    //  Helper
    // ********************************************* //
    // ********************************************* //

    /** \brief assert that a size_t belongs to [[0,2]] */
    void assert_size(const size_t& k) const;

};

/** \brief + operator */
v3 operator+(const double& s,const v3& p);
/** \brief - operator */
v3 operator-(const double& s,const v3& p);
/** \brief multiply by a scalar operator */
v3 operator*(const double& s,const v3& p);

// ********************************************* //
// ********************************************* //
//  Output
// ********************************************* //
// ********************************************* //

/** \brief output the vector in ostream as (x,y,z) */
std::ostream& operator<<(std::ostream& stream,const v3& p);

/** \brief Special exception class for v3 */
class exception_v3 : public exception_proj
{
public:

    /** \brief empty constructor */
    exception_v3():exception_proj(){}
    /** \brief constructor with error information */
    exception_v3(const std::string& msg,const std::string& file,const std::string& caller,const int& line):exception_proj(msg,file,caller,line){}
};

}



#endif
