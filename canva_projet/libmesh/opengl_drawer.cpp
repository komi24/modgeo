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

#include <opengl_drawer.hpp>

#include <mesh.hpp>

#include <iostream>
#include <sstream>
#include <GL/glu.h>

namespace proj
{
  void opengl_drawer::draw(const mesh& m)
  {
      unsigned int N_tri=m.number_of_triangle();
      const int* p_connectivity=&m.get_connectivity()[0];
      const double* p_vertex=m.get_vertices()[0].pointer();
      const double* p_normal=m.get_normal()[0].pointer();
      const double* p_texture=m.get_texture()[0].pointer();
      const double* p_color=m.get_color()[0].pointer();

      bool is_texture=(m.get_texture().size()==m.get_vertices().size());
      bool is_color=(m.get_color().size()==m.get_vertices().size());

      if(m.get_normal().size()!=m.get_vertices().size())
      {
          std::stringstream msg;
          msg<<"Error, incorrect normals for this mesh "<<std::endl;
          msg<<"Number of vertices: ["<<m.get_vertices().size()<<"] / Number of normales ["<<m.get_normal().size()<<"]";
          if(m.get_normal().size()==0)
              msg<<std::endl<<"(Use mesh.compute_normal() before drawing)"<<std::endl;
          throw proj::exception_proj(msg.str(),__FILE__,__FUNCTION__,__LINE__);
      }


      //enable client state
      glEnableClientState(GL_VERTEX_ARRAY);
      glEnableClientState(GL_NORMAL_ARRAY);
      if(is_texture)
          glEnableClientState(GL_TEXTURE_COORD_ARRAY);
      if(is_color)
          glEnableClientState(GL_COLOR_ARRAY);

      //setup pointers
      glVertexPointer(3,GL_DOUBLE,0,p_vertex);
      glNormalPointer(GL_DOUBLE,0,p_normal);
      if(is_texture)
          glTexCoordPointer(2,GL_DOUBLE,0,p_texture);
      if(is_color)
          glColorPointer(3,GL_DOUBLE,0,p_color);

      //draw triangles
      glDrawElements(GL_TRIANGLES,3*N_tri,GL_UNSIGNED_INT,p_connectivity);

      //disable client state
      glDisableClientState(GL_VERTEX_ARRAY);
      glDisableClientState(GL_NORMAL_ARRAY);
      if(is_texture)
          glDisableClientState(GL_TEXTURE_COORD_ARRAY);
      if(is_color)
          glDisableClientState(GL_COLOR_ARRAY);

  }
}
