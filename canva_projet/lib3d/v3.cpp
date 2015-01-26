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



#include <v3.hpp>

#include <v2.hpp>
#include <cmath>
#include <sstream>

#include <assert.h>

namespace proj
{

    v3::v3():internal_x(0),internal_y(0),internal_z(0){}
    v3::v3(const double& x,const double& y,const double& z):internal_x(x),internal_y(y),internal_z(z){}
    const double& v3::x() const
    {
        return internal_x;
    }

    double& v3::x()
    {
        return internal_x;
    }

    const double& v3::y() const
    {
        return internal_y;
    }

    double& v3::y()
    {
        return internal_y;
    }

    const double& v3::z() const
    {
        return internal_z;
    }

    double& v3::z()
    {
        return internal_z;
    }

    const double& v3::operator[](const size_t& k) const
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
	  default:
	    assert(false);
        throw proj::exception_v3("Probleme",__FILE__,__FUNCTION__,__LINE__);
	  };
    }

    double& v3::operator[](const size_t& k)
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
	  default:
	    assert(false);
        throw proj::exception_v3("Probleme",__FILE__,__FUNCTION__,__LINE__);
	  };
    }

    const double& v3::operator()(const size_t& k) const
    {
      return (*this)[k];
    }
    double& v3::operator()(const size_t& k)
    {
      return (*this)[k];
    }

    void v3::set_zero()
    {
        internal_x=0;
        internal_y=0;
        internal_z=0;
    }

    double v3::dot(const v3& p) const
    {
        return internal_x*p.x()+internal_y*p.y()+internal_z*p.z();
    }

    double v3::norm() const
    {
        return std::sqrt(norm2());
    }

    double v3::norm2() const
    {
        return internal_x*internal_x+internal_y*internal_y+internal_z*internal_z;
    }

    v3 v3::cross(const v3& p) const
    {
        return v3(internal_y*p.z()-internal_z*p.y(),
                  internal_z*p.x()-internal_x*p.z(),
                  internal_x*p.y()-internal_y*p.x()
                  );
    }
    v3 v3::operator+(const v3& p2) const
    {
        return v3(x()+p2.x(),y()+p2.y(),z()+p2.z());
    }

    v3 operator+(const double& s,const v3& p)
    {
        return v3(s+p.x(),s+p.y(),s+p.z());
    }

    v3 v3::operator+(const double& s) const
    {
        v3 temp=*this;
        temp+=s;
        return temp;
    }

    v3 v3::operator-(const v3& p2) const
    {
        return v3(x()-p2.x(),y()-p2.y(),z()-p2.z());
    }

    v3 operator-(const double& s,const v3& p)
    {
        return v3(s-p.x(),s-p.y(),s-p.z());
    }

    v3 v3::operator-(const double& s) const
    {
        return v3(x()-s,y()-s,z()-s);
    }

    v3 operator*(const double& s,const v3& p)
    {
        return v3(p.x()*s,p.y()*s,p.z()*s);
    }

    v3 v3::operator*(const double& s) const
    {
        v3 temp=*this;
        temp*=s;
        return temp;
    }

    v3 v3::operator/(const double& s) const
    {
      double epsilon=1e-8;
      if(std::abs(s)<epsilon)
          throw proj::exception_v3("Division par 0",__FILE__,__FUNCTION__,__LINE__);

      return v3(x()/s,y()/s,z()/s);
    }

    v3& v3::operator+=(const v3& p)
    {
        internal_x+=p.x();
        internal_y+=p.y();
        internal_z+=p.z();
        return *this;
    }

    v3& v3::operator+=(const double& s)
    {
        internal_x+=s;
        internal_y+=s;
        internal_z+=s;
        return *this;
    }

    v3& v3::operator-=(const v3& p)
    {
        internal_x-=p.x();
        internal_y-=p.y();
        internal_z-=p.z();
        return *this;
    }

    v3& v3::operator-=(const double& s)
    {
        internal_x-=s;
        internal_y-=s;
        internal_z-=s;
        return *this;
    }

    v3& v3::operator*=(const double& s)
    {
        internal_x*=s;
        internal_y*=s;
        internal_z*=s;
        return *this;
    }

    v3& v3::operator/=(const double& s)
    {
        internal_x/=s;
        internal_y/=s;
        internal_z/=s;
        return *this;
    }

    v3 v3::operator-() const
    {
        return v3(-internal_x,-internal_y,-internal_z);
    }

    v3 v3::product_compontentwise(const v3& p) const
    {
        return v3(internal_x*p.x(),internal_y*p.y(),internal_z*p.z());
    }

    v3& v3::product_compontentwise_internal(const v3& p)
    {
        internal_x*=p.x();
        internal_y*=p.y();
        internal_z*=p.z();
        return *this;
    }
    std::string v3::to_string() const
    {
        std::stringstream stream;
        stream<<internal_x<<" "<<internal_y<<" "<<internal_z;
        return stream.str();
    }
    std::ostream& operator<<(std::ostream& stream,const v3& p)
    {
        stream<<"("<<p.to_string()<<")";
        return stream;
    }

    void v3::assert_size(const size_t& k) const
    {
        if(k>2)
        {
            std::stringstream stream;
            stream<<"v3::assert_size("<<k<<") k>2";
            throw exception_v3(stream.str(),__FILE__,__FUNCTION__,__LINE__);
        }
    }
    v3 v3::normalized() const
    {
        double epsilon=1e-6;

        double n=norm();
        if(n<epsilon){
            std::cerr << "division par zero dans v3.cpp 278" <<std::endl;
            return *this/(n+1e-5);
            // TO De comment throw exception_v3("norm=0",__FILE__,__FUNCTION__,__LINE__);
        }
        return *this/n;
    }
    void v3::scale(const double& sx,const double& sy,const double& sz)
    {
        internal_x*=sx;
        internal_y*=sy;
        internal_z*=sz;
    }

    v2 v3::to_v2() const{return v2(internal_x,internal_y);}

    const double *v3::pointer() const
    {return &internal_x;}
}
