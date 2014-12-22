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



#ifndef V2_HPP
#define V2_HPP

#include <string>
#include <iostream>

#include <exception_proj.hpp>

namespace proj
{

/** \brief Vectors/Points 2D */
class v2
{
public:

    // ********************************************* //
    // ********************************************* //
    //  CONSTRUCTORS
    // ********************************************* //
    // ********************************************* //

    /** \brief empty constructor */
    v2();
    /** \brief direct constructor */
    v2(const double& x,const double& y);

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


    /** \brief Access to the k_th entry (k in [0,1]) */
    const double& operator[](const size_t& k) const;
    /** \brief Access to the k_th entry (k in [0,1]) */
    double& operator[](const size_t& k);
    /** \brief Access to the k_th entry (k in [0,1]) */
    const double& operator()(const size_t& k) const;
    /** \brief Access to the k_th entry (k in [0,1]) */
    double& operator()(const size_t& k);

    /** \brief set every entry to 0 */
    void set_zero();


    /** \brief fast pointer access
        \warning unprotected access */
    const double *pointer() const;

    // ********************************************* //
    // ********************************************* //
    //  Math operation
    // ********************************************* //
    // ********************************************* //

    /** \brief perform dot product between two v2 */
    double dot(const v2& p) const;

    /** \brief get the norm of the vector */
    double norm() const;
    /** \brief get the square norm of the vector */
    double norm2() const;
    /** \brief normalize the vector to unit length */
    v2 normalized() const;




    // ********************************************* //
    // ********************************************* //
    //  Operator +-*/
    // ********************************************* //
    // ********************************************* //

    /** \brief + operator */
    v2 operator+(const v2& p2) const;
    /** \brief + operator */
    v2 operator+(const double& s) const;

    /** \brief - operator */
    v2 operator-(const v2& p2) const;
    /** \brief - operator */
    v2 operator-(const double& s) const;


    /** \brief multiply by a scalar operator */
    v2 operator*(const double& s) const;
    /** \brief divide by a scalar operator */
    v2 operator/(const double& s) const;

    /** \brief internal + */
    v2& operator+=(const v2& p);
    /** \brief internal + */
    v2& operator+=(const double& s);
    /** \brief internal - */
    v2& operator-=(const v2& p);
    /** \brief internal - */
    v2& operator-=(const double& s);
    /** \brief internal * */
    v2& operator*=(const double& s);
    /** \brief internal / */
    v2& operator/=(const double& s);

    /** \brief unary negation */
    v2 operator-() const;

    /** \brief does componentwise mutliplication
            \return MC_v2d(x*p.x(),y*p.y(),z*p.z())
        */
    v2 product_compontentwise(const v2& p) const;
    /** \brief does componentwise mutliplication

            perform p=(p.x()*p2.x(),p.y()*p2.x())
        */
    v2& product_compontentwise_internal(const v2& p);
    /** \brief internal scaling (similar to componentwise) */
    void scale(const double& sx,const double& sy);


    // ********************************************* //
    // ********************************************* //
    //  Output
    // ********************************************* //
    // ********************************************* //

    /** \brief export the value as string cout<<v2(2,3,6) => 2 3 6 */
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


    // ********************************************* //
    // ********************************************* //
    //  Helper
    // ********************************************* //
    // ********************************************* //

    /** \brief assert that a size_t belongs to [[0,1]] */
    void assert_size(const size_t& k) const;

};

/** \brief + operator */
v2 operator+(const double& s,const v2& p);
/** \brief - operator */
v2 operator-(const double& s,const v2& p);
/** \brief multiply by a scalar operator */
v2 operator*(const double& s,const v2& p);

// ********************************************* //
// ********************************************* //
//  Output
// ********************************************* //
// ********************************************* //

/** \brief output the vector in ostream as (x,y,z) */
std::ostream& operator<<(std::ostream& stream,const v2& p);


/** \brief Special exception class for v2 */
class exception_v2 : public exception_proj
{
public:

    /** \brief empty constructor */
    exception_v2():exception_proj(){}
    /** \brief constructor with error information */
    exception_v2(const std::string& msg,const std::string& file,const std::string& caller,const int& line):exception_proj(msg,file,caller,line){}
};

}



#endif
