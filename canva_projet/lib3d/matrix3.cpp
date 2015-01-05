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


#include <matrix3.hpp>
#include <v3.hpp>
#include <cmath>
#include <iostream>
#include <sstream>


namespace proj
{

matrix3::matrix3()
{
    m[0]=1;m[3]=0;m[6]=0;
    m[1]=0;m[4]=1;m[7]=0;
    m[2]=0;m[5]=0;m[8]=1;
}

matrix3::matrix3(const double& x00,const double& x01,const double& x02,
                 const double& x10,const double& x11,const double& x12,
                 const double& x20,const double& x21,const double& x22)
{
    m[0]=x00;m[3]=x01;m[6]=x02;
    m[1]=x10;m[4]=x11;m[7]=x12;
    m[2]=x20;m[5]=x21;m[8]=x22;
}
matrix3 matrix3::identity()
{
    return matrix3(1,0,0,0,1,0,0,0,1);
}
matrix3 matrix3::zeros()
{
    return matrix3(0,0,0,0,0,0,0,0,0);
}


matrix3 matrix3::rotation(const v3& axis,const double& angle)
{
    v3 n=axis.normalized();

    double cos_t=std::cos(angle);
    double sin_t=std::sin(angle);

    return matrix3(cos_t+n[0]*n[0]*(1-cos_t),n[0]*n[1]*(1-cos_t)-n[2]*sin_t,n[1]*sin_t+n[0]*n[2]*(1-cos_t),
                   n[2]*sin_t+n[0]*n[1]*(1-cos_t),cos_t+n[1]*n[1]*(1.0-cos_t),-n[0]*sin_t+n[1]*n[2]*(1-cos_t),
                   -n[1]*sin_t+n[0]*n[2]*(1-cos_t),n[0]*sin_t+n[1]*n[2]*(1-cos_t),cos_t+n[2]*n[2]*(1-cos_t));

}

matrix3 matrix3::scale(const double& s)
{
    return matrix3(s,0,0,0,s,0,0,0,s);
}

matrix3 matrix3::scale(const double& s_x,const double& s_y,const double& s_z)
{
    return matrix3(s_x,0,0,0,s_y,0,0,0,s_z);
}

const double& matrix3::operator()(const size_t& k1,const size_t& k2) const
{
    assert_size(k1,k2);
    return m[3*k2+k1];
}
double& matrix3::operator()(const size_t& k1,const size_t& k2)
{
    assert_size(k1,k2);
    return m[3*k2+k1];
}

matrix3 matrix3::operator+(const matrix3& m2) const
{
    matrix3 temp=*this;
    temp+=m2;
    return temp;
}

matrix3 operator+(const double& s,const matrix3& m)
{
    matrix3 temp=m;
    temp+=s;
    return temp;
}

matrix3 matrix3::operator+(const double& s) const
{
    matrix3 temp=*this;
    temp+=s;
    return temp;
}

matrix3 matrix3::operator-(const matrix3& m2) const
{
    const double* pm2=m2.pointer();

    return matrix3(m[0]-pm2[0],m[3]-pm2[3],m[6]-pm2[6],
                   m[1]-pm2[1],m[4]-pm2[4],m[7]-pm2[7],
                   m[2]-pm2[2],m[5]-pm2[5],m[8]-pm2[8]);
}

matrix3 operator-(const double& s,const matrix3& m)
{
    const double* pm=m.pointer();
    return matrix3(s-pm[0],s-pm[3],s-pm[6],
                   s-pm[1],s-pm[4],s-pm[7],
                   s-pm[2],s-pm[5],s-pm[8]);
}

matrix3 matrix3::operator-(const double& s) const
{
    return matrix3(m[0]-s,m[3]-s,m[6]-s,
                   m[1]-s,m[4]-s,m[7]-s,
                   m[2]-s,m[5]-s,m[8]-s);
}

matrix3 operator*(const double& s,const matrix3& m)
{
    matrix3 temp=m;
    temp*=s;
    return temp;
}

matrix3 matrix3::operator*(const double& s) const
{
    matrix3 temp=*this;
    temp*=s;
    return temp;
}

v3 matrix3::operator*(const v3& v) const
{
    double x0=v.x();
    double y0=v.y();
    double z0=v.z();

    return v3(m[0]*x0+m[3]*y0+m[6]*z0,
              m[1]*x0+m[4]*y0+m[7]*z0,
              m[2]*x0+m[5]*y0+m[8]*z0);
}

matrix3 matrix3::operator*(const matrix3& m2) const
{
    const double* pm2=m2.m;

    matrix3 current=matrix3::zeros();
    double *p=current.pointer_unprotected();
    for(unsigned int k0=0;k0<3;++k0)
        for(unsigned int k1=0;k1<3;++k1)
            for(unsigned int ks=0;ks<3;++ks)
                p[k0+3*k1] += m[3*ks+k0]*pm2[3*k1+ks];
    return current;
}

matrix3 matrix3::operator/(const double& s) const
{
    return matrix3(m[0]/s,m[3]/s,m[6]/s,
                   m[1]/s,m[4]/s,m[7]/s,
                   m[2]/s,m[5]/s,m[8]/s);
}

matrix3& matrix3::operator+=(const matrix3& _m)
{
    const double* pm=_m.m;
    for(unsigned int k=0;k<9;++k)
        m[k] += pm[k];
    return *this;
}

matrix3& matrix3::operator+=(const double& s)
{
    for(unsigned int k=0;k<9;++k)
        m[k] += s;
    return *this;
}

matrix3& matrix3::operator-=(const matrix3& _m)
{
    const double* pm=_m.m;
    for(unsigned int k=0;k<9;++k)
        m[k] -= pm[k];
    return *this;
}

matrix3& matrix3::operator-=(const double& s)
{
    for(unsigned int k=0;k<9;++k)
        m[k] -= s;
    return *this;
}

matrix3& matrix3::operator*=(const double& s)
{
    for(unsigned int k=0;k<9;++k)
        m[k] *= s;
    return *this;
}

matrix3& matrix3::operator/=(const double& s)
{
    for(unsigned int k=0;k<9;++k)
        m[k] /= s;
    return *this;
}

matrix3 matrix3::operator-() const
{
    return matrix3(-m[0],-m[3],-m[6],
                   -m[1],-m[4],-m[7],
                   -m[2],-m[5],-m[8]);
}
matrix3 matrix3::product_compontentwise(const matrix3& _m) const
{
    const double* pm=_m.m;
    return matrix3(m[0]*pm[0],m[3]*pm[3],m[6]*pm[6],
                   m[1]*pm[1],m[4]*pm[4],m[7]*pm[7],
                   m[2]*pm[2],m[5]*pm[5],m[8]*pm[8]);
}

matrix3& matrix3::product_compontentwise_internal(const matrix3& _m)
{
    const double* pm=_m.m;
    for(unsigned int k=0;k<9;++k)
        m[k]=pm[k];
    return *this;
}

std::ostream& operator<<(std::ostream& stream,const matrix3& _m)
{
    const double* pm=_m.pointer();
    stream<<pm[0]<<","<<pm[3]<<","<<pm[6]<<"\n"<<
            pm[1]<<","<<pm[4]<<","<<pm[7]<<"\n"<<
            pm[2]<<","<<pm[5]<<","<<pm[8]<<"\n";
    return stream;
}

void matrix3::assert_size(const size_t& k1,const size_t& k2) const
{
    if(k1>2 || k2>2)
    {
        std::stringstream stream;
        stream<<"matrix3::assert_size("<<k1<<","<<k2<<") > (2,2)";
        throw exception_matrix3(stream.str(),__FILE__,__FUNCTION__,__LINE__);
    }
}

const double* matrix3::pointer() const
{
    return m;
}
double* matrix3::pointer_unprotected()
{
    return m;
}
std::vector<double> matrix3::to_vector() const
{
    std::vector<double> m3d(9);
    for(unsigned int kx=0;kx<3;++kx)
        for(unsigned int ky=0;ky<3;++ky)
            m3d[3*ky+kx]=m[3*ky+kx];
    return m3d;
}

matrix3 matrix3::transposed() const
{
    return matrix3(m[0],m[1],m[2],
                   m[3],m[4],m[5],
                   m[6],m[7],m[8]);
}

}
