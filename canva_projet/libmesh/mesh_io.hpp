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



#ifndef MESH_IO_HPP
#define MESH_IO_HPP

#include <string>

namespace proj
{

class mesh;


/** \brief Helper class for I/O mesh*/
class mesh_io
{
    public:

    /** \brief load a off file */
    static mesh load_off_file(const std::string& filename);

    /** \brief load a obj file */
    static mesh load_obj_file(const std::string& filename);
};
}

#endif
