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


#include <matrix2.hpp>
#include <v2.hpp>
#include <cmath>
#include <iostream>
#include <sstream>


namespace proj
{

matrix2::matrix2()
{
    m[0]=1;m[2]=0;
    m[1]=0;m[3]=1;
}

matrix2::matrix2(const double& x00,const double& x01,
                 const double& x10,const double& x11)
{
    m[0]=x00;m[2]=x01;
    m[1]=x10;m[3]=x11;
}
matrix2 matrix2::identity()
{
    return matrix2(1,0,
                   0,1);
}
matrix2 matrix2::zeros()
{
    return matrix2(0,0,
                   0,0);
}


matrix2 matrix2::rotation(const double& angle)
{
    double cos_t=std::cos(angle);
    double sin_t=std::sin(angle);

    return matrix2(cos_t,-sin_t,
                   sin_t, cos_t);
}

matrix2 matrix2::scale(const double& s)
{
    return matrix2(s,0,
                   0,s);
}

matrix2 matrix2::scale(const double& s_x,const double& s_y)
{
    return matrix2(s_x,0,
                   0,s_y);
}

const double& matrix2::operator()(const size_t& k1,const size_t& k2) const
{
    assert_size(k1,k2);
    return m[2*k2+k1];
}
double& matrix2::operator()(const size_t& k1,const size_t& k2)
{
    assert_size(k1,k2);
    return m[2*k2+k1];
}

matrix2 matrix2::operator+(const matrix2& m2) const
{
    const double* pm2=m2.m;

    return matrix2(m[0]+pm2[0],m[2]+pm2[2],
                   m[1]+pm2[1],m[3]+pm2[3]);
}

matrix2 operator+(const double& s,const matrix2& m)
{
    matrix2 temp=m;
    temp+=s;
    return temp;
}

matrix2 matrix2::operator+(const double& s) const
{
    matrix2 temp=*this;
    temp+=s;
    return temp;
}

matrix2 matrix2::operator-(const matrix2& m2) const
{
    matrix2 temp=*this;
    temp-=m2;
    return temp;
}

matrix2 operator-(const double& s,const matrix2& m)
{
    const double* pm=m.pointer();
    return matrix2(s-pm[0],s-pm[2],
                   s-pm[1],s-pm[3]);
}

matrix2 matrix2::operator-(const double& s) const
{
    return matrix2(m[0]-s,m[3]-s,
                   m[1]-s,m[4]-s);
}

matrix2 operator*(const double& s,const matrix2& m)
{
    matrix2 temp=m;
    temp*=s;
    return temp;
}

matrix2 matrix2::operator*(const double& s) const
{
    matrix2 temp=*this;
    temp*=s;
    return temp;
}

v2 matrix2::operator*(const v2& v) const
{
    double x0=v.x();
    double y0=v.y();

    return v2(m[0]*x0+m[2]*y0,
              m[1]*x0+m[3]*y0);
}

matrix2 matrix2::operator*(const matrix2& m2) const
{
    const double* pm2=m2.m;

    matrix2 current=matrix2::zeros();
    double *p=current.pointer_unprotected();
    for(unsigned int k0=0;k0<2;++k0)
        for(unsigned int k1=0;k1<2;++k1)
            for(unsigned int ks=0;ks<2;++ks)
                p[k0+2*k1] += m[2*ks+k0]*pm2[2*k1+ks];
    return current;
}

matrix2 matrix2::operator/(const double& s) const
{
    return matrix2(m[0]/s,m[2]/s,
                   m[1]/s,m[3]/s);
}

matrix2& matrix2::operator+=(const matrix2& _m)
{
    const double* pm=_m.m;
    for(unsigned int k=0;k<4;++k)
        m[k] += pm[k];
    return *this;
}

matrix2& matrix2::operator+=(const double& s)
{
    for(unsigned int k=0;k<4;++k)
        m[k] += s;
    return *this;
}

matrix2& matrix2::operator-=(const matrix2& _m)
{
    const double* pm=_m.m;
    for(unsigned int k=0;k<4;++k)
        m[k] -= pm[k];
    return *this;
}

matrix2& matrix2::operator-=(const double& s)
{
    for(unsigned int k=0;k<4;++k)
        m[k] -= s;
    return *this;
}

matrix2& matrix2::operator*=(const double& s)
{
    for(unsigned int k=0;k<4;++k)
        m[k] *= s;
    return *this;
}

matrix2& matrix2::operator/=(const double& s)
{
    for(unsigned int k=0;k<4;++k)
        m[k] /= s;
    return *this;
}

matrix2 matrix2::operator-() const
{
    return matrix2(-m[0],-m[2],
                   -m[1],-m[3]);
}
matrix2 matrix2::product_compontentwise(const matrix2& _m) const
{
    const double* pm=_m.m;
    return matrix2(m[0]*pm[0],m[2]*pm[2],
                   m[1]*pm[1],m[3]*pm[3]);
}

matrix2& matrix2::product_compontentwise_internal(const matrix2& _m)
{
    const double* pm=_m.m;
    for(unsigned int k=0;k<4;++k)
        m[k]=pm[k];
    return *this;
}

std::ostream& operator<<(std::ostream& stream,const matrix2& _m)
{
    const double* pm=_m.pointer();
    stream<<pm[0]<<","<<pm[3]<<"\n"<<
            pm[1]<<","<<pm[4]<<"\n";
    return stream;
}

void matrix2::assert_size(const size_t& k1,const size_t& k2) const
{
    if(k1>1 || k2>1)
    {
        std::stringstream stream;
        stream<<"matrix2::assert_size("<<k1<<","<<k2<<") > (1,1)";
        throw exception_matrix2(stream.str(),__FILE__,__FUNCTION__,__LINE__);
    }
}

const double* matrix2::pointer() const
{
    return m;
}
double* matrix2::pointer_unprotected()
{
    return m;
}
std::vector<double> matrix2::to_vector() const
{
    std::vector<double> m3d(4);
    for(unsigned int kx=0;kx<2;++kx)
        for(unsigned int ky=0;ky<2;++ky)
            m3d[2*ky+kx]=m[2*ky+kx];
    return m3d;
}

matrix2 matrix2::transposed() const
{
    return matrix2(m[0],m[1],
                   m[2],m[3]);
}

}
