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

#ifndef QUATERNION_HPP
#define QUATERNION_HPP

#include <v4.hpp>

namespace proj
{
class matrix3;

/** \brief Quaternion class */
class quaternion : public v4
{
public:
    // ********************************************* //
    // ********************************************* //
    //  CONSTRUCTORS
    // ********************************************* //
    // ********************************************* //

    /** \brief default constructor */
    quaternion();
    /** \brief constructor from axis and angle */
    quaternion(const v3& axis,const double& angle);
    /** \brief direct constructor */
    quaternion(const v4& v);
    /** \brief direct constructor */
    quaternion(const double& x,const double& y,const double& z,const double& w);


    // ********************************************* //
    // ********************************************* //
    //  GET
    // ********************************************* //
    // ********************************************* //

    /** \brief get the unit axis corresponding to the quaternion */
    v3 axis() const;
    /** \brief get the angle corresponding to the quaternion */
    double angle() const;

    // ********************************************* //
    // ********************************************* //
    //  Math
    // ********************************************* //
    // ********************************************* //

    /** \brief compute the rotation matrix associated to the current quaternion
        \return a 3x3 rotation matrix
    */
    matrix3 matrix() const;

    /** \brief get the conjugate of the current quaterion */
    quaternion conjugated() const;

    /** \brief Spherical Linear Interpolation SLERP

        Use (sin((1-t) theta )q0 +sin(t theta)q1)/sin(theta)
        But same results with (q1 q0^{-1})^{t} q0
        (q1*q0.invert()).pow_q(t)*q0) */
    static quaternion slerp(const quaternion& q0,const quaternion& q1,const double alpha);

    /** \brief apply a rotation (encoded by the quaternion) to the vector/point 3D */
    v3 rotate(const v3& vec) const;


    // ********************************************* //
    // ********************************************* //
    //  Operators
    // ********************************************* //
    // ********************************************* //

    /** \brief internal multiplication by other quaternion */
    quaternion& operator*=(const quaternion& q);
    /** \brief internal multiplication by a scalar */
    quaternion& operator*=(const double& s);
    /** \brief internal addition with other quaternion */
    quaternion& operator+=(const quaternion& q);
    /** \brief internal substraction with other quaternion */
    quaternion& operator-=(const quaternion& q);
    /** \brief internal division by a scalar */
    quaternion& operator/=(const double& s);
    
    /** \brief multiplication by other quaternion */
    quaternion operator*(const quaternion& q) const;
    /** \brief multiplication with a v3 seen as a quaternion (v.w()=0) */
    quaternion operator*(const v3& v) const;
    /** \brief multiplication with scalar */
    quaternion operator*(const double& s) const;
    /** \brief addition with other quaternionn */
    quaternion operator+(const quaternion& q) const;
    /** \brief substraction with other quaternionn */
    quaternion operator-(const quaternion& q) const;
    /** \brief division by a scalar */
    quaternion operator/(const double& s) const;

    /** \brief unary negation */
    quaternion operator-() const;





    
private:

};

/** \brief multiplication with scalar */
quaternion operator*(const double& s,const quaternion& q);


/** \brief Special exception class for v4 */
class exception_quaternion : public exception_v4
{
public:

    /** \brief empty constructor */
    exception_quaternion():exception_v4(){}
    /** \brief constructor with error information */
    exception_quaternion(const std::string& msg,const std::string& file,const std::string& caller,const int& line):exception_v4(msg,file,caller,line){}
};


}

#endif
