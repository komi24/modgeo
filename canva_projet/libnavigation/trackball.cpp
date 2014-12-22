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
#include <trackball.hpp>

#include <cmath>

namespace proj
{

    trackball::trackball()
        :disc_radius(0.8)
    {
    }


    double trackball::project_to_disc(const double& x,const double& y) const
    {
        double n=std::sqrt(x*x+y*y);
        if(n<disc_radius*0.707107)
            return sqrt(disc_radius*disc_radius-n*n);
        else
            return disc_radius*disc_radius/(2.0*n);
    }

    void trackball::set_2d_coords(const double& x0,const double& y0,const double& x1,const double& y1)
    {
        //axis of the rotation
        v3 axis;
        // angle of the rotation
        double phi;

        //security to not move if start=end
//        double epsilon=1e-3;
        double epsilon=1e-10;
        if( pow((x0-x1)*(x0-x1)+(y0-y1)*(y0-y1),0.5)<epsilon)
//            d_q=quaternion(v4(1,0,0,0));
            return;
        else
        {
            // temp position
            v3 p1,p2;

            p1=v3(x0,y0,project_to_disc(x0,y0));
            p2=v3(x1,y1,project_to_disc(x1,y1));
            axis = (p1.cross(p2)).normalized();

            v3 u=p1-p2;
            double t=u.norm()/(2*disc_radius);
            t=std::min(std::max(t,-1.0),1.0); //clamp
            phi = 2.0*asin(t);

            //compute quaternion to apply
            d_q=quaternion(axis,phi);
        }
    }

    void trackball::apply_rotation()
    {current_q=current_q*d_q.conjugated();}
    void trackball::no_motion()
    {d_q=quaternion(v4(1,0,0,0));}


    const quaternion& trackball::quat() const{return current_q;}
    quaternion& trackball::quat(){return current_q;}

    const quaternion& trackball::d_quat() const {return d_q;}
    quaternion& trackball::d_quat() {return d_q;}

    double& trackball::radius() {return disc_radius;}
    const double& trackball::radius() const {return disc_radius;}

}
