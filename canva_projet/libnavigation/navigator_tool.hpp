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



#ifndef NAVIGATOR_TOOL_HPP
#define NAVIGATOR_TOOL_HPP

#include <trackball.hpp>
#include <v3.hpp>

#include <vector>

namespace proj
{

    /** \brief (Dirty) Container class for camera, mouse and fps manipulation

        The camera is controled using 3 parameters:

        1/ zoom factor (dist)  = translation along local z coordinate

        2/ orientation (track) = rotation transformation in this second frame controlled by arcball

        3/ translation (tr)    = final translation in the global world space

    */
    class navigator_tool
    {
    public:

        // ********************************************* //
        // ********************************************* //
        //  CONSTRUCTORS
        // ********************************************* //
        // ********************************************* //

        /** \brief empty constructor */
        navigator_tool();


        // ********************************************* //
        // ********************************************* //
        //  Screen parameters
        // ********************************************* //
        // ********************************************* //

        /** \brief Window size x */
        unsigned int& screen_size_x();
        /** \brief Window size x */
        const unsigned int& screen_size_x() const;

        /** \brief Window size y */
        unsigned int& screen_size_y();
        /** \brief Window size y */
        const unsigned int& screen_size_y() const;


        // ********************************************* //
        // ********************************************* //
        //  Camera manipulation
        // ********************************************* //
        // ********************************************* //

        /** \brief zoom factor */
        double& dist_cam();
        /** \brief zoom factor */
        const double& dist_cam() const;

        /** \brief move the camera forward by a distance dL */
        void go_forward(const double& dL);
        /** \brief move the camera to the right by a distance dL */
        void go_right  (const double& dL);
        /** \brief move the camera up by a distance dL */
        void go_up     (const double& dL);


        /** \brief camera rotation using on-screen coordinates */
        void trackball_rotate(const int& x,const int&y);
        /** \brief camera zoom using on-screen coordinates */
        void trackball_zoom(const int& y);


        // ********************************************* //
        // ********************************************* //
        //  Mouse record
        // ********************************************* //
        // ********************************************* //

        /** \brief previous position of the mouse in screen x-coordinate */
        int& x_previous();
        /** \brief previous position of the mouse in screen x-coordinate */
        const int& x_previous() const;

        /** \brief previous position of the mouse in screen y-coordinate */
        int& y_previous();
        /** \brief previous position of the mouse in screen y-coordinate */
        const int& y_previous() const;

        /** \brief is left button clicked */
        bool& left_button();
        /** \brief is left button clicked */
        const bool& left_button() const;

        /** \brief is right button clicked */
        bool& right_button();
        /** \brief is right button clicked */
        const bool& right_button() const;




        // ********************************************* //
        // ********************************************* //
        // Projection parameters
        // ********************************************* //
        // ********************************************* //

        /** \brief Projection camera parameters: left/top/znear/zfar/aspect

         for use: glFrustum(left, -left, top, -top, znear, zfar);
         with
           double aspect=static_cast<double>(navigator.x_screen_size_1)/static_cast<double>(navigator.y_screen_size_1);
           double fov=45.0*PI/180.0;
           double near=0.1;
           double top=tan(fov*0.5)*near;
           double bottom=-top;
           double left=aspect*bottom;
           double right=-left;
         */
        std::vector<double> projection_param() const;


        // ********************************************* //
        // ********************************************* //
        //  Camera orientation
        // ********************************************* //
        // ********************************************* //

        /** \brief get the camera orientation (matrix of the quaternion) */
        matrix3 camera_orientation();
        /** \brief get the camera absolute translation */
        v3 camera_translation();



        // ********************************************* //
        // ********************************************* //
        //  FPS
        // ********************************************* //
        // ********************************************* //

        /** \brief increase the frame number by 1 */
        void increase_frame_number();

        /** \brief get the current elapsed time */
        const unsigned int& time() const;
        /** \brief get the current elapsed time */
        unsigned int& time();

        /** \brief update the fps counter and set frame to 0*/
        double update_fps();
        /** \brief elapsed time since old_time record */
        double delta_time();

        /** \brief get the current fps */
        double fps();

    private:


        // ********************************************* //
        // ********************************************* //
        //  Internal Camera Parameters
        // ********************************************* //
        // ********************************************* //

        /** \brief internal rotation quaternion controled using ArcBall */
        trackball track;
        /** \brief internal camera world space translation */
        v3 tr;
        /** \brief internal zoom magnitude (z-translation in local coordinate frame) */
        double dist;

        /** \brief internal camera FOV storage */
        double fov;
        /** \brief internal camera Znear storage */
        double znear;
        /** \brief internal camera Zfar storage */
        double zfar;

        // ********************************************* //
        // ********************************************* //
        //  Window and mouse parameters
        // ********************************************* //
        // ********************************************* //

        /** \brief internal storage of window width */
        unsigned int x_size;
        /** \brief internal storage of window height */
        unsigned int y_size;

        /** \brief internal storage of previous clicked position of the mouse (x) */
        int mouse_x_previous;
        /** \brief internal storage of previous clicked position of the mouse (y) */
        int mouse_y_previous;


        /** \brief internal storage when left button is clicked */
        bool is_left_button;
        /** \brief internal storage when right button is clicked */
        bool is_right_button;

        // ********************************************* //
        // ********************************************* //
        //  Time parameter
        // ********************************************* //
        // ********************************************* //

        /** \brief internal storage of current fps */
        double current_fps;
        /** \brief internal storage of current time */
        unsigned int current_time;
        /** \brief internal storage of previously recorded time */
        unsigned int old_time;
        /** \brief internal storage of current frame number */
        unsigned int frame;

    };
}

#endif
