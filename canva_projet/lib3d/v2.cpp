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



#include <v2.hpp>

#include <cmath>
#include <sstream>

#include <assert.h>

namespace proj
{

v2::v2():internal_x(0),internal_y(0){}
v2::v2(const double& x,const double& y):internal_x(x),internal_y(y){}
const double& v2::x() const
{
    return internal_x;
}

double& v2::x()
{
    return internal_x;
}

const double& v2::y() const
{
    return internal_y;
}

double& v2::y()
{
    return internal_y;
}


const double& v2::operator[](const size_t& k) const
{
    assert_size(k);
    switch (k)
    {
    case 0:
        return internal_x;
    case 1:
        return internal_y;
    default:
        assert(false);
        throw proj::exception_v2("Probleme",__FILE__,__FUNCTION__,__LINE__);
    };
}

double& v2::operator[](const size_t& k)
{
    assert_size(k);
    switch (k)
    {
    case 0:
        return internal_x;
    case 1:
        return internal_y;
    default:
        assert(false);
        throw proj::exception_v2("Probleme",__FILE__,__FUNCTION__,__LINE__);
    };
}

const double& v2::operator()(const size_t& k) const
{
    return (*this)[k];
}
double& v2::operator()(const size_t& k)
{
    return (*this)[k];
}

void v2::set_zero()
{
    internal_x=0;
    internal_y=0;
}

double v2::dot(const v2& p) const
{
    return internal_x*p.x()+internal_y*p.y();
}

double v2::norm() const
{
    return std::sqrt(norm2());
}

double v2::norm2() const
{
    return internal_x*internal_x+internal_y*internal_y;
}

v2 v2::operator+(const v2& p2) const
{
    return v2(x()+p2.x(),y()+p2.y());
}

v2 operator+(const double& s,const v2& p)
{
    return v2(s+p.x(),s+p.y());
}

v2 v2::operator+(const double& s) const
{
    v2 temp=*this;
    temp+=s;
    return temp;
}

v2 v2::operator-(const v2& p2) const
{
    return v2(x()-p2.x(),y()-p2.y());
}

v2 operator-(const double& s,const v2& p)
{
    return v2(s-p.x(),s-p.y());
}

v2 v2::operator-(const double& s) const
{
    return v2(x()-s,y()-s);
}

v2 operator*(const double& s,const v2& p)
{
    return v2(p.x()*s,p.y()*s);
}

v2 v2::operator*(const double& s) const
{
    return v2(s*x(),s*y());
}

v2 v2::operator/(const double& s) const
{
    double epsilon=1e-8;
    if(std::abs(s)<epsilon)
        throw proj::exception_v2("Division par 0",__FILE__,__FUNCTION__,__LINE__);

    return v2(x()/s,y()/s);
}

v2& v2::operator+=(const v2& p)
{
    internal_x+=p.x();
    internal_y+=p.y();
    return *this;
}

v2& v2::operator+=(const double& s)
{
    internal_x+=s;
    internal_y+=s;
    return *this;
}

v2& v2::operator-=(const v2& p)
{
    internal_x-=p.x();
    internal_y-=p.y();
    return *this;
}

v2& v2::operator-=(const double& s)
{
    internal_x-=s;
    internal_y-=s;
    return *this;
}

v2& v2::operator*=(const double& s)
{
    internal_x*=s;
    internal_y*=s;
    return *this;
}

v2& v2::operator/=(const double& s)
{
    internal_x/=s;
    internal_y/=s;
    return *this;
}

v2 v2::operator-() const
{
    return v2(-internal_x,-internal_y);
}

v2 v2::product_compontentwise(const v2& p) const
{
    return v2(internal_x*p.x(),internal_y*p.y());
}

v2& v2::product_compontentwise_internal(const v2& p)
{
    internal_x*=p.x();
    internal_y*=p.y();
    return *this;
}
std::string v2::to_string() const
{
    std::stringstream stream;
    stream<<internal_x<<" "<<internal_y;
    return stream.str();
}
std::ostream& operator<<(std::ostream& stream,const v2& p)
{
    stream<<"("<<p.to_string()<<")";
    return stream;
}

void v2::assert_size(const size_t& k) const
{
    if(k>1)
    {
        std::stringstream stream;
        stream<<"v2::assert_size("<<k<<") k>2";
        throw exception_v2(stream.str(),__FILE__,__FUNCTION__,__LINE__);
    }
}
v2 v2::normalized() const
{
    double epsilon=1e-6;

    double n=norm();
    if(n<epsilon)
        throw exception_v2("norm=0",__FILE__,__FUNCTION__,__LINE__);

    return *this/n;
}
void v2::scale(const double& sx,const double& sy)
{
    internal_x*=sx;
    internal_y*=sy;
}

const double *v2::pointer() const
{return &internal_x;}
}
