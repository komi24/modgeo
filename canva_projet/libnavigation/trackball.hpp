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

#ifndef   	TRACKBALL_HPP
# define   	TRACKBALL_HPP




#include <quaternion.hpp>

namespace proj
{

    /// A container class to deal with a trackball, use ArcBall paradigm
    class trackball
    {
    public:

        // ********************************************* //
        // ********************************************* //
        //  CONSTRUCTORS
        // ********************************************* //
        // ********************************************* //

        /** \empty initial constructor */
        trackball();


        //*********************************************//
        //*********************************************//
        // Get quaternion
        //*********************************************//
        //*********************************************//

        /** \brief get the current quaternion */
        const quaternion& quat() const;
        /** \brief get the current quaternion */
        quaternion& quat();

        /** \brief get the quaternion to apply */
        const quaternion& d_quat() const;
        /** \brief get the quaternion to apply */
        quaternion& d_quat();

        //*********************************************//
        //*********************************************//
        // Disc radius
        //*********************************************//
        //*********************************************//

        /** \brief get the disc radius */
        double& radius();
        /** \brief get the disc radius */
        const double& radius() const;

        //*********************************************//
        //*********************************************//
        // Manipulation
        //*********************************************//
        //*********************************************//

        /** \brief return the distance to disc for the 3D coordinate */
        double project_to_disc(const double& x,const double& y) const;

        /** \brief given a set of 2d coords difference, return the corresponding quaternion */
        void set_2d_coords(const double& x0,const double& y0,const double& x1,const double& y1);

        /** \brief multiply d_q to current_q */
        void apply_rotation();

        /** \brief Set d_q to 0 */
        void no_motion();





    private:

        /** \brief the current quaternion */
        quaternion current_q;
        /** \brief the quaternion to apply */
        quaternion d_q;

        /** \brief internal parameter of the disc radius */
        double disc_radius;

    };

}

#endif
