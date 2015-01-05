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



#include <navigator_tool.hpp>

#include <cmath>

#include <matrix3.hpp>

namespace proj
{

    navigator_tool::navigator_tool()
        :x_size(800),y_size(800),mouse_x_previous(0),mouse_y_previous(0),is_left_button(false),is_right_button(false)
    {
        fov=45.0*M_PI/180.0;
        znear=1e-2;
        zfar=150;
        dist=-4.0;

        track.quat()=quaternion(v3(0,0,1),M_PI);

    }

    unsigned int& navigator_tool::screen_size_x(){return x_size;}
    const unsigned int& navigator_tool::screen_size_x() const{return x_size;}

    unsigned int& navigator_tool::screen_size_y(){return y_size;}
    const unsigned int& navigator_tool::screen_size_y() const{return y_size;}

    double& navigator_tool::dist_cam() {return dist;}
    const double& navigator_tool::dist_cam() const {return dist;}

    void navigator_tool::go_forward(const double& d_L)
    {
        v3 z(0,0,1);
        tr += d_L*(track.quat().rotate(z));
    }

    void navigator_tool::go_right  (const double& d_L)
    {
        v3 x(-1,0,0);
        tr += d_L*(track.quat().rotate(x));
    }

    void navigator_tool::go_up     (const double& d_L)
    {
        v3 y(0,1,0);
        tr += d_L*(track.quat().rotate(y));
    }

    int& navigator_tool::x_previous() {return mouse_x_previous;}
    const int& navigator_tool::x_previous() const {return mouse_x_previous;}

    int& navigator_tool::y_previous() {return mouse_y_previous;}
    const int& navigator_tool::y_previous() const {return mouse_y_previous;}


    bool& navigator_tool::left_button() {return is_left_button;}
    const bool& navigator_tool::left_button() const {return is_left_button;}

    bool& navigator_tool::right_button() {return is_right_button;}
    const bool& navigator_tool::right_button() const {return is_right_button;}

    void navigator_tool::trackball_rotate(const int& x,const int&y)
    {
        const double& x_old=mouse_x_previous;
        const double& y_old=mouse_y_previous;
        const double& w=y_size;
        const double& h=x_size;

        track.set_2d_coords((2.0*x_old-w)/w , (2.0*y_old-h)/h , (2*x-w)/w , (2*y-h)/h);
        track.apply_rotation();
        mouse_x_previous=x;
        mouse_y_previous=y;
    }

    void navigator_tool::trackball_zoom(const int& y)
    {
        //magnification factor
        const double F0=500;

        const double& y_old=mouse_y_previous;

        double u = y-y_old;
        double fu= u/F0;

        dist += (std::fabs(dist)+1)*fu;
        dist = std::min(dist,0.0);
        mouse_y_previous=y;

    }

    std::vector<double> navigator_tool::projection_param() const
    {
        double aspect=static_cast<double>(x_size)/static_cast<double>(y_size);
        double top=std::tan(fov*0.5)*znear;
        double left=-aspect*top;
        std::vector<double> param;
        param.push_back(left);
        param.push_back(top);
        param.push_back(znear);
        param.push_back(zfar);
        param.push_back(aspect);

        return param;
    }

    matrix3 navigator_tool::camera_orientation()
    {
        return track.quat().conjugated().matrix();
    }
    v3 navigator_tool::camera_translation()
    {
        return tr;
    }

    void navigator_tool::increase_frame_number() {++frame;}

    const unsigned int& navigator_tool::time() const {return current_time;}
    unsigned int& navigator_tool::time() {return current_time;}

    double navigator_tool::update_fps()
    {
        current_fps=static_cast<double>(frame*1000)/static_cast<double>(current_time-old_time);
        old_time=current_time;
        frame=0;
        return current_fps;
    }
    double navigator_tool::delta_time()
    {
        return current_time-old_time;
    }

    double navigator_tool::fps()
    {
        return current_fps;
    }


}
