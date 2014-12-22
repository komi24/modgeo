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

#ifndef DEBUG_MESH_HPP
#define DEBUG_MESH_HPP

#include <vector>
#include <v3.hpp>

class glwidget;

namespace proj
{


class mesh;

class debug_mesh
{
public:

    debug_mesh();

    void set_glwidget(glwidget *widget);

    /** \brief Draw mesh in debug mode (draw indices) */
    void draw_debug(proj::mesh& mesh_current);



    //debug variables
    void set_is_debug_mode(bool);
    void set_is_debug_vertex_index(bool);
    void set_is_debug_face_index(bool);
    void set_is_debug_inverted_normal(bool);
    void set_is_debug_vertex_point(bool);

private:

    bool is_debug_mode;
    bool is_debug_vertex_index;
    bool is_debug_face_index;
    bool is_debug_inverted_normal;
    bool is_debug_draw_vertex;
    void draw_index(const std::vector<proj::v3>& x);
    void draw_index_face(const proj::mesh& mesh,const std::vector<proj::v3>& translate);

    glwidget *p_widget;
};
}

#endif
