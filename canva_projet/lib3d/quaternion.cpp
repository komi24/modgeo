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

#include <quaternion.hpp>
#include <matrix3.hpp>
#include <v3.hpp>
#include <cmath>

namespace proj
{
quaternion::quaternion()
    :v4(1,0,0,0)
{}
quaternion::quaternion(const double& x,const double& y,const double& z,const double& w)
    :v4(x,y,z,w)
{}

quaternion::quaternion(const v3& axis,const double& angle)
{
    double sin_phi=std::sin(angle/2.0);
    double cos_phi=std::cos(angle/2.0);
    v3 n_axis=axis.normalized();

    x() = n_axis[0]*sin_phi;
    y() = n_axis[1]*sin_phi;
    z() = n_axis[2]*sin_phi;
    w() =           cos_phi;
}

quaternion::quaternion(const v4& v)
    :v4(v)
{}

v3 quaternion::axis() const
{
    return v3(x(),y(),z()).normalized();
}
double quaternion::angle() const
{
    return 2*std::acos(w());
}

matrix3 quaternion::matrix() const
{
    double x2=x()*x();
    double y2=y()*y();
    double z2=z()*z();
    double xy=x()*y();
    double xz=x()*z();
    double yz=y()*z();
    double wx=w()*x();
    double wy=w()*y();
    double wz=w()*z();

    return matrix3(1-2*(y2+z2),  2*(xy-wz),  2*(xz+wy),
                   2*(xy+wz),1-2*(x2+z2),  2*(yz-wx),
                   2*(xz-wy),  2*(yz+wx),1-2*(x2+y2));
}

quaternion quaternion::conjugated() const
{
    return quaternion(v4(-x(),-y(),-z(),w()));
}

quaternion quaternion::slerp(const quaternion& q0,const quaternion& q1,const double t)
{
    quaternion q0_local=q0;
    double epsilon=1e-6;

    //do not interpolate for very small differences
    if( (q0-q1).norm()<epsilon )
        return q0;

    double cos_theta = q0.dot(q1);
    if(cos_theta<0)
    {
        q0_local=-q0;
        cos_theta*=-1;
    }



    double sin_theta = sqrt(1-cos_theta*cos_theta);
    double theta = atan2(sin_theta,cos_theta);

    //linear interpolation for small angles
    if(std::abs(sin_theta)<epsilon)
        return (1-t)*q0_local+t*q1;

    const double w0=sin((1-t) *theta)/sin_theta;
    const double w1=sin(  t   *theta)/sin_theta;

    quaternion interpolated = w0*q0_local+w1*q1;

    return interpolated;
}

v3 quaternion::rotate(const v3& v) const
{
    double x2=x()*x();
    double y2=y()*y();
    double z2=z()*z();
    double xy=x()*y();
    double xz=x()*z();
    double yz=y()*z();
    double wx=w()*x();
    double wy=w()*y();
    double wz=w()*z();

    //identical to (*this)*vec*quaternion(-x,-y,-z,w);
    return v3( (1-2*(y2+z2))*v.x() + 2*(xy-wz)*v.y() + 2*(xz+wy)*v.z(),
               2*(xy+wz)*v.x()+(1-2*(x2+z2))*v.y()+2*(yz-wx)*v.z(),
               2*(xz-wy)*v.x()+2*(yz+wx)*v.y()+(1-2*(x2+y2))*v.z() );
}

quaternion& quaternion::operator*=(const quaternion& q)
{
    //identical to (w0*v1+w1*v0-v0xv1,w0*w1-v0.v1), with v0=(x,y,z) & v1=(q.x,q.y,q.z).

    *this =quaternion(  (x() * q.w()) + (w() * q.x()) + (y() * q.z()) - (z() * q.y()),
                        (y() * q.w()) + (w() * q.y()) + (z() * q.x()) - (x() * q.z()),
                        (z() * q.w()) + (w() * q.z()) + (x() * q.y()) - (y() * q.x()),
                        (w() * q.w()) - (x() * q.x()) - (y() * q.y()) - (z() * q.z()) );


    return *this;
}
quaternion& quaternion::operator*=(const double& s)
{
    x()*=s;
    y()*=s;
    z()*=s;
    w()*=s;
    return *this;
}

quaternion& quaternion::operator+=(const quaternion& q)
{
    x()+=q.x();
    y()+=q.y();
    z()+=q.z();
    w()+=q.w();
    return *this;
}
quaternion& quaternion::operator-=(const quaternion& q)
{
    x()-=q.x();
    y()-=q.y();
    z()-=q.z();
    w()-=q.w();
    return *this;
}
quaternion& quaternion::operator/=(const double& s)
{
    double epsilon=1e-8;
    if(std::abs(s)<epsilon)
        throw proj::exception_v4("Division par 0",__FILE__,__FUNCTION__,__LINE__);

    x()/=s;
    y()/=s;
    z()/=s;
    w()/=s;
    return *this;
}

quaternion quaternion::operator*(const quaternion& q) const
{
    quaternion temp=*this;
    temp*=q;
    return temp;
}
quaternion quaternion::operator*(const v3& v) const
{
    return quaternion(  (w() * v.x()) + (y() * v.z()) - (z() * v.y()),
                        (w() * v.y()) + (z() * v.x()) - (x() * v.z()),
                        (w() * v.z()) + (x() * v.y()) - (y() * v.x()),
                       -(x() * v.x()) - (y() * v.y()) - (z() * v.z()) );
}
quaternion quaternion::operator*(const double& s) const
{
    quaternion temp=*this;
    temp*=s;
    return temp;
}
quaternion operator*(const double& s,const quaternion& q)
{
    return q*s;
}
quaternion quaternion::operator+(const quaternion& q) const
{
    quaternion temp=*this;
    temp+=q;
    return temp;
}
quaternion quaternion::operator-(const quaternion& q) const
{
    quaternion temp=*this;
    temp-=q;
    return temp;
}
quaternion quaternion::operator/(const double& s) const
{
    quaternion temp=*this;
    temp/=s;
    return temp;
}

quaternion quaternion::operator-() const
{
    return quaternion(v4(-x(),-y(),-z(),-w()));
}


}
