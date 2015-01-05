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



#include <v4.hpp>

#include <v3.hpp>
#include <v2.hpp>

#include <cmath>
#include <sstream>

#include <assert.h>

namespace proj
{

v4::v4():internal_x(0),internal_y(0),internal_z(0),internal_w(0){}
v4::v4(const double& x,const double& y,const double& z,const double& w):internal_x(x),internal_y(y),internal_z(z),internal_w(w){}
const double& v4::x() const
{
    return internal_x;
}

double& v4::x()
{
    return internal_x;
}

const double& v4::y() const
{
    return internal_y;
}

double& v4::y()
{
    return internal_y;
}

const double& v4::z() const
{
    return internal_z;
}

double& v4::z()
{
    return internal_z;
}
const double& v4::w() const
{
    return internal_w;
}

double& v4::w()
{
    return internal_w;
}

const double& v4::operator[](const size_t& k) const
{
    assert_size(k);
    switch (k)
    {
    case 0:
        return internal_x;
    case 1:
        return internal_y;
    case 2:
        return internal_z;
    case 3:
        return internal_w;
    default:
        assert(false);
        throw proj::exception_v4("Probleme",__FILE__,__FUNCTION__,__LINE__);
    };
}

double& v4::operator[](const size_t& k)
{
    assert_size(k);
    switch (k)
    {
    case 0:
        return internal_x;
    case 1:
        return internal_y;
    case 2:
        return internal_z;
    case 3:
        return internal_w;
    default:
        assert(false);
        throw proj::exception_v4("Probleme",__FILE__,__FUNCTION__,__LINE__);
    };
}

const double& v4::operator()(const size_t& k) const
{
    return (*this)[k];
}

double& v4::operator()(const size_t& k)
{
    return (*this)[k];
}

void v4::set_zero()
{
    internal_x=0;
    internal_y=0;
    internal_z=0;
    internal_w=0;
}

double v4::dot(const v4& p) const
{
    return internal_x*p.x()+internal_y*p.y()+internal_z*p.z()+internal_w*p.w();
}

double v4::norm() const
{
    return std::sqrt(norm2());
}

double v4::norm2() const
{
    return internal_x*internal_x+internal_y*internal_y+internal_z*internal_z+internal_w*internal_w;
}


v4 v4::operator+(const v4& p2) const
{
    return v4(x()+p2.x(),y()+p2.y(),z()+p2.z(),w()+p2.w());
}

v4 operator+(const double& s,const v4& p)
{
    return v4(s+p.x(),s+p.y(),s+p.z(),s+p.w());
}

v4 v4::operator+(const double& s) const
{
    v4 temp=*this;
    temp+=s;
    return temp;
}

v4 v4::operator-(const v4& p2) const
{
    return v4(x()-p2.x(),y()-p2.y(),z()-p2.z(),w()-p2.w());
}

v4 operator-(const double& s,const v4& p)
{
    return v4(s-p.x(),s-p.y(),s-p.z(),s-p.w());
}

v4 v4::operator-(const double& s) const
{
    return v4(x()-s,y()-s,z()-s,w()-s);
}

v4 operator*(const double& s,const v4& p)
{
    return v4(p.x()*s,p.y()*s,p.z()*s,p.w()*s);
}

v4 v4::operator*(const double& s) const
{
    v4 temp=*this;
    temp*=s;
    return temp;
}

v4 v4::operator/(const double& s) const
{
    double epsilon=1e-8;
    if(std::abs(s)<epsilon)
        throw proj::exception_v4("Division par 0",__FILE__,__FUNCTION__,__LINE__);
    return v4(x()/s,y()/s,z()/s,w()/s);
}

v4& v4::operator+=(const v4& p)
{
    internal_x+=p.x();
    internal_y+=p.y();
    internal_z+=p.z();
    internal_w+=p.w();
    return *this;
}

v4& v4::operator+=(const double& s)
{
    internal_x+=s;
    internal_y+=s;
    internal_z+=s;
    internal_w+=s;
    return *this;
}

v4& v4::operator-=(const v4& p)
{
    internal_x-=p.x();
    internal_y-=p.y();
    internal_z-=p.z();
    internal_w-=p.w();

    return *this;
}

v4& v4::operator-=(const double& s)
{
    internal_x-=s;
    internal_y-=s;
    internal_z-=s;
    internal_w-=s;
    return *this;
}

v4& v4::operator*=(const double& s)
{
    internal_x*=s;
    internal_y*=s;
    internal_z*=s;
    internal_w*=s;
    return *this;
}

v4& v4::operator/=(const double& s)
{
    double epsilon=1e-8;
    if(std::abs(s)<epsilon)
        throw proj::exception_v4("Division par 0",__FILE__,__FUNCTION__,__LINE__);

    internal_x/=s;
    internal_y/=s;
    internal_z/=s;
    internal_w/=s;
    return *this;
}

v4 v4::operator-() const
{
    return v4(-internal_x,-internal_y,-internal_z,-internal_w);
}

v4 v4::product_compontentwise(const v4& p) const
{
    return v4(internal_x*p.x(),internal_y*p.y(),internal_z*p.z(),internal_w*p.w());
}

v4& v4::product_compontentwise_internal(const v4& p)
{
    internal_x*=p.x();
    internal_y*=p.y();
    internal_z*=p.z();
    internal_w*=p.w();
    return *this;
}
std::string v4::to_string() const
{
    std::stringstream stream;
    stream<<internal_x<<" "<<internal_y<<" "<<internal_z<<" "<<internal_w;
    return stream.str();
}
std::ostream& operator<<(std::ostream& stream,const v4& p)
{
    stream<<"("<<p.to_string()<<")";
    return stream;
}

void v4::assert_size(const size_t& k) const
{
    if(k>3)
    {
        std::stringstream stream;
        stream<<"v4::assert_size("<<k<<") k>3";
        throw exception_v4(stream.str(),__FILE__,__FUNCTION__,__LINE__);
    }
}
v4 v4::normalized() const
{
    double epsilon=1e-6;

    double n=norm();
    if(n<epsilon)
        throw exception_v4("norm=0",__FILE__,__FUNCTION__,__LINE__);
    return *this/n;
}
void v4::scale(const double& sx,const double& sy,const double& sz,const double& sw)
{
    internal_x*=sx;
    internal_y*=sy;
    internal_z*=sz;
    internal_w*=sw;
}

v3 v4::to_v3() const{return v3(internal_x,internal_y,internal_z);}
v2 v4::to_v2() const{return v2(internal_x,internal_y);}

const double *v4::pointer() const
{return &internal_x;}

}
