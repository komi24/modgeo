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


#include <matrix4.hpp>

#include <matrix3.hpp>
#include <v3.hpp>
#include <v4.hpp>
#include <cmath>
#include <iostream>
#include <sstream>


namespace proj
{

matrix4::matrix4()
{
    m[0]=1;m[4]=0;m[8]=0;m[12]=0;
    m[1]=0;m[5]=1;m[9]=0;m[13]=0;
    m[2]=0;m[6]=0;m[10]=1;m[14]=0;
    m[3]=0;m[7]=0;m[11]=0;m[15]=1;
}

matrix4::matrix4(const double& x00,const double& x01,const double& x02,const double& x03,
                 const double& x10,const double& x11,const double& x12,const double& x13,
                 const double& x20,const double& x21,const double& x22,const double& x23,
                 const double& x30,const double& x31,const double& x32,const double& x33)
{
    m[0]=x00;m[4]=x01;m[8]=x02;m[12]=x03;
    m[1]=x10;m[5]=x11;m[9]=x12;m[13]=x13;
    m[2]=x20;m[6]=x21;m[10]=x22;m[14]=x23;
    m[3]=x30;m[7]=x31;m[11]=x32;m[15]=x33;
}

matrix4::matrix4(const matrix3& m3)
{
    m[0]=m3(0,0);m[4]=m3(0,1);m[8]=m3(0,2);m[12]=0;
    m[1]=m3(1,0);m[5]=m3(1,1);m[9]=m3(1,2);m[13]=0;
    m[2]=m3(2,0);m[6]=m3(2,1);m[10]=m3(2,2);m[14]=0;
    m[3]=0;m[7]=0;m[11]=0;m[15]=1;
}

matrix4 matrix4::identity()
{
    return matrix4(1,0,0,0,
                   0,1,0,0,
                   0,0,1,0,
                   0,0,0,1);
}
matrix4 matrix4::zeros()
{
    return matrix4(0,0,0,0,
                   0,0,0,0,
                   0,0,0,0,
                   0,0,0,0);
}


matrix4 matrix4::rotation(const v3& axis,const double& angle)
{
    v3 n=axis.normalized();

    double cos_t=std::cos(angle);
    double sin_t=std::sin(angle);

    return matrix4(cos_t+n[0]*n[0]*(1-cos_t),n[0]*n[1]*(1-cos_t)-n[2]*sin_t,n[1]*sin_t+n[0]*n[2]*(1-cos_t),0,
                   n[2]*sin_t+n[0]*n[1]*(1-cos_t),cos_t+n[1]*n[1]*(1.0-cos_t),-n[0]*sin_t+n[1]*n[2]*(1-cos_t),0,
                   -n[1]*sin_t+n[0]*n[2]*(1-cos_t),n[0]*sin_t+n[1]*n[2]*(1-cos_t),cos_t+n[2]*n[2]*(1-cos_t),0,
                   0,0,0,1);

}

matrix4 matrix4::scale(const double& s)
{
    return matrix4(s,0,0,0,
                   0,s,0,0,
                   0,0,s,0,
                   0,0,0,1);
}

matrix4 matrix4::scale(const double& s_x,const double& s_y,const double& s_z,const double& s_w)
{
    return matrix4(s_x,0.0,0.0,0.0,
                   0.0,s_y,0.0,0.0,
                   0.0,0.0,s_z,0.0,
                   0.0,0.0,0.0,s_w);
}
matrix4 matrix4::translation(const v3& translation)
{
    return matrix4(1,0,0,translation.x(),
                   0,1,0,translation.y(),
                   0,0,1,translation.z(),
                   0,0,0,1);
}

matrix4 matrix4::transformation(const matrix3& m3,const v3& translation)
{
    return matrix4(m3(0,0),m3(0,1),m3(0,2),translation.x(),
                   m3(1,0),m3(1,1),m3(1,2),translation.y(),
                   m3(2,0),m3(2,1),m3(2,2),translation.z(),
                   0,0,0,1);
}

const double& matrix4::operator()(const size_t& k1,const size_t& k2) const
{
    assert_size(k1,k2);
    return m[4*k2+k1];
}
double& matrix4::operator()(const size_t& k1,const size_t& k2)
{
    assert_size(k1,k2);
    return m[4*k2+k1];
}

matrix4 matrix4::operator+(const matrix4& m2) const
{
    const double* pm2=m2.pointer();

    return matrix4(m[0]+pm2[0],m[4]+pm2[4],m[8]+pm2[8],m[12]+pm2[12],
                   m[1]+pm2[1],m[5]+pm2[5],m[9]+pm2[9],m[13]+pm2[13],
                   m[2]+pm2[2],m[6]+pm2[6],m[10]+pm2[10],m[14]+pm2[14],
                   m[3]+pm2[3],m[7]+pm2[7],m[11]+pm2[11],m[15]+pm2[15]);
}

matrix4 operator+(const double& s,const matrix4& m)
{
    const double* pm=m.pointer();
    return matrix4(pm[0]+s,pm[4]+s,pm[8]+s,pm[12]+s,
                   pm[1]+s,pm[5]+s,pm[9]+s,pm[13]+s,
                   pm[2]+s,pm[6]+s,pm[10]+s,pm[14]+s,
                   pm[3]+s,pm[7]+s,pm[11]+s,pm[15]+s);
}

matrix4 matrix4::operator+(const double& s) const
{
    return s+(*this);
}

matrix4 matrix4::operator-(const matrix4& m2) const
{
    const double* pm2=m2.m;

    return matrix4(m[0]-pm2[0],m[4]-pm2[4],m[8]-pm2[8],m[12]-pm2[12],
                   m[1]-pm2[1],m[5]-pm2[5],m[9]-pm2[9],m[13]-pm2[13],
                   m[2]-pm2[2],m[6]-pm2[6],m[10]-pm2[10],m[14]-pm2[14],
                   m[3]-pm2[3],m[7]-pm2[7],m[11]-pm2[11],m[15]-pm2[15]);
}

matrix4 operator-(const double& s,const matrix4& m)
{
    const double* pm=m.pointer();
    return matrix4(s-pm[0],s-pm[4],s-pm[8],s-pm[12],
                   s-pm[1],s-pm[5],s-pm[9],s-pm[13],
                   s-pm[2],s-pm[6],s-pm[10],s-pm[14],
                   s-pm[3],s-pm[7],s-pm[11],s-pm[15]);
}

matrix4 matrix4::operator-(const double& s) const
{
    return matrix4(m[0]-s,m[4]-s,m[8]-s,m[12]-s,
                   m[1]-s,m[5]-s,m[9]-s,m[13]-s,
                   m[2]-s,m[6]-s,m[10]-s,m[14]-s,
                   m[3]-s,m[7]-s,m[11]-s,m[15]-s);
}

matrix4 operator*(const double& s,const matrix4& m)
{
    const double* pm=m.pointer();
    return matrix4(pm[0]*s,pm[4]*s,pm[8]*s,pm[12]*s,
                   pm[1]*s,pm[5]*s,pm[9]*s,pm[13]*s,
                   pm[2]*s,pm[6]*s,pm[10]*s,pm[14]*s,
                   pm[3]*s,pm[7]*s,pm[11]*s,pm[15]*s);
}

matrix4 matrix4::operator*(const double& s) const
{
    matrix4 m;m*=s;
    return m;
}

v4 matrix4::operator*(const v4& v) const
{
    const double& x0=v.x();
    const double& y0=v.y();
    const double& z0=v.z();
    const double& w0=v.w();

    return v4(m[0]*x0+m[4]*y0+m[8]*z0+m[12]*w0,
              m[1]*x0+m[5]*y0+m[9]*z0+m[13]*w0,
              m[2]*x0+m[6]*y0+m[10]*z0+m[14]*w0,
              m[3]*x0+m[7]*y0+m[11]*z0+m[15]*w0);
}
v3 matrix4::operator*(const v3& v) const
{
    const double& x0=v.x();
    const double& y0=v.y();
    const double& z0=v.z();

    double w=m[3]*x0+m[7]*y0+m[11]*z0+m[15];

    double epsilon=1e-8;
    if(std::abs(w)<epsilon)
        throw proj::exception_matrix4("Norme=0",__FILE__,__FUNCTION__,__LINE__);

    return v3(m[0]*x0+m[4]*y0+m[8]*z0+m[12],
              m[1]*x0+m[5]*y0+m[9]*z0+m[13],
              m[2]*x0+m[6]*y0+m[10]*z0+m[14])/w;
}

matrix4 matrix4::operator*(const matrix4& m2) const
{
    const double* pm2=m2.m;

    matrix4 current=matrix4::zeros();
    double *p=current.pointer_unprotected();
    for(unsigned int k0=0;k0<4;++k0)
        for(unsigned int k1=0;k1<4;++k1)
            for(unsigned int ks=0;ks<4;++ks)
                p[k0+4*k1] += m[4*ks+k0]*pm2[4*k1+ks];
    return current;
}

matrix4 matrix4::operator/(const double& s) const
{
    return matrix4(m[0]/s,m[4]/s,m[8]/s,m[12]/s,
                   m[1]/s,m[5]/s,m[9]/s,m[13]/s,
                   m[2]/s,m[6]/s,m[10]/s,m[14]/s,
                   m[3]/s,m[7]/s,m[11]/s,m[15]/s);
}

matrix4& matrix4::operator+=(const matrix4& _m)
{
    const double* pm=_m.m;
    for(unsigned int k=0;k<16;++k)
        m[k] += pm[k];
    return *this;
}

matrix4& matrix4::operator+=(const double& s)
{
    for(unsigned int k=0;k<16;++k)
        m[k] += s;
    return *this;
}

matrix4& matrix4::operator-=(const matrix4& _m)
{
    const double* pm=_m.m;
    for(unsigned int k=0;k<16;++k)
        m[k] -= pm[k];
    return *this;
}

matrix4& matrix4::operator-=(const double& s)
{
    for(unsigned int k=0;k<16;++k)
        m[k] -= s;
    return *this;
}

matrix4& matrix4::operator*=(const double& s)
{
    for(unsigned int k=0;k<16;++k)
        m[k] *= s;
    return *this;
}

matrix4& matrix4::operator/=(const double& s)
{
    for(unsigned int k=0;k<16;++k)
        m[k] /= s;
    return *this;
}

matrix4 matrix4::operator-() const
{
    return matrix4(-m[0],-m[4],-m[8],-m[12],
                   -m[1],-m[5],-m[9],-m[13],
                   -m[2],-m[6],-m[10],-m[14],
                   -m[3],-m[7],-m[11],-m[15]);
}
matrix4 matrix4::product_compontentwise(const matrix4& _m) const
{
    const double* pm=_m.m;
    return matrix4(m[0]*pm[0],m[4]*pm[4],m[8]*pm[8],m[12]*pm[12],
                   m[1]*pm[1],m[5]*pm[5],m[9]*pm[9],m[13]*pm[13],
                   m[2]*pm[2],m[6]*pm[6],m[10]*pm[10],m[14]*pm[14],
                   m[3]*pm[3],m[7]*pm[7],m[11]*pm[11],m[15]*pm[15]);
}

matrix4& matrix4::product_compontentwise_internal(const matrix4& _m)
{
    const double* pm=_m.m;
    for(unsigned int k=0;k<16;++k)
        m[k]=pm[k];
    return *this;
}

std::ostream& operator<<(std::ostream& stream,const matrix4& _m)
{
    const double* pm=_m.pointer();
    stream<<pm[0]<<","<<pm[4]<<","<<pm[8]<<","<<pm[12]<<"\n"<<
            pm[1]<<","<<pm[5]<<","<<pm[9]<<","<<pm[13]<<"\n"<<
            pm[2]<<","<<pm[6]<<","<<pm[10]<<","<<pm[14]<<"\n"<<
            pm[3]<<","<<pm[7]<<","<<pm[11]<<","<<pm[15]<<"\n";
    return stream;
}

void matrix4::assert_size(const size_t& k1,const size_t& k2) const
{
    if(k1>3 || k2>3)
    {
        std::stringstream stream;
        stream<<"matrix3::assert_size("<<k1<<","<<k2<<") > (3,3)";
        throw exception_matrix4(stream.str(),__FILE__,__FUNCTION__,__LINE__);
    }
}

const double* matrix4::pointer() const
{
    return m;
}
double* matrix4::pointer_unprotected()
{
    return m;
}
std::vector<double> matrix4::to_vector() const
{
    std::vector<double> m4d(16);
    for(unsigned int kx=0;kx<4;++kx)
        for(unsigned int ky=0;ky<4;++ky)
            m4d[4*ky+kx]=m[4*ky+kx];
    return m4d;
}

matrix4 matrix4::transposed() const
{
    return matrix4(m[0],m[1],m[2],m[3],
                   m[4],m[5],m[6],m[7],
                   m[8],m[9],m[10],m[11],
                   m[12],m[13],m[14],m[15]);
}

matrix4 matrix4::projection_perspective(const double& fovy,const double& aspect,const double& z_near,const double& z_far)
{
    const double f=1.0/tan(fovy/2.0);
    const double fp=f/aspect;

    const double L=z_near-z_far;
    const double epsilon=1e-8;
    if(std::abs(L)<epsilon)
        throw proj::exception_matrix4("z_far-z_near too small",__FILE__,__FUNCTION__,__LINE__);

    const double C=(z_far+z_near)/L;
    const double D=(2*z_far*z_near)/L;

    return matrix4(fp , 0, 0, 0,
                   0  , f, 0, 0,
                   0  , 0, C, D,
                   0  , 0,-1, 0);
}

matrix4 matrix4::projection_frustum(const double& left,const double& right,const double& bottom,const double& top,const double& near,const double& far)
{
    const double width=right-left;
    const double height=top-bottom;
    const double L=far-near;

    const double epsilon=1e-8;
    if(std::abs(width)<epsilon ||
            std::abs(height)<epsilon ||
            std::abs(L)<epsilon)
        throw proj::exception_matrix4("bad camera projection",__FILE__,__FUNCTION__,__LINE__);

    const double fw=2*near/width;
    const double fh=2*near/height;
    const double A=(right+left)/width;
    const double B=(top+bottom)/height;
    const double C=-(far+near)/L;
    const double D=-2*far*near/L;

    return matrix4(fw , 0, A, 0,
                   0  ,fh, B, 0,
                   0  , 0, C, D,
                   0  , 0,-1, 0);
}

matrix4 matrix4::projection_orthographic(const double& left,const double& right,const double& bottom,const double& top,const double& near,const double& far)
{
    const double width=right-left;
    const double height=top-bottom;
    const double L=far-near;

    const double epsilon=1e-8;
    if(std::abs(width)<epsilon ||
            std::abs(height)<epsilon ||
            std::abs(L)<epsilon)
        throw proj::exception_matrix4("bad camera projection",__FILE__,__FUNCTION__,__LINE__);

    const double sx= 2.0/width;
    const double sy= 2.0/height;
    const double sz=-2.0/L;
    const double tx=-(right+left)/width;
    const double ty=-(top+bottom)/height;
    const double tz=-(far+near)/L;


    return matrix4(sx , 0, 0,tx,
                   0  ,sy, 0,ty,
                   0  , 0,sz,tz,
                   0  , 0, 0, 1);
}

matrix4 matrix4::projection_look_at(const matrix4& current_matrix,const v3& eye,const v3& center,const v3& up)
{
    v3 f=(center-eye).normalized();
    v3 s=f.cross(up);
    v3 u=s.cross(f);

    matrix4 M( s.x(), s.y(), s.z(), 0,
               u.x(), u.y(), u.z(), 0,
              -f.x(),-f.y(),-f.z(), 0,
                  0 ,    0 ,    0 , 1);


    matrix4 T=matrix4::translation(-eye);
    M=M*T;
    M=current_matrix*M;



    return M;
}


matrix4 matrix4::translated(const v3& translation) const
{
    matrix4 temp=*this;
    temp.translate_internal(translation);
    return temp;
}

void matrix4::translate_internal(const v3& translation)
{
    m[12]+=translation.x();
    m[13]+=translation.y();
    m[14]+=translation.z();
}

}
