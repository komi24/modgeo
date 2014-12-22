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


#include <debug_mesh.hpp>

#include <mesh.hpp>
#include <glwidget.hpp>

#include <assert.h>

namespace proj
{

debug_mesh::debug_mesh()
{
    //debug variables
    is_debug_mode=false;

    is_debug_vertex_index=true;
    is_debug_face_index=true;
    is_debug_inverted_normal=false;
    is_debug_draw_vertex=true;

    p_widget=NULL;
}





void debug_mesh::draw_debug(proj::mesh& mesh_current)
{
    assert(p_widget!=NULL);

    if(is_debug_mode==false)
        return ;

    double L_text=0.02;
    if(is_debug_inverted_normal==true)
        L_text*=-1;


    std::vector<v3> nv=mesh_current.get_normal_per_vertex();
    std::vector<v3> np=mesh_current.get_normal_per_polygon();

    glEnable(GL_LIGHTING);
    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(5,5);



    glColor3d(0.5,0.1,0.0);

    glDisable(GL_POLYGON_OFFSET_FILL);
    glDisable(GL_LIGHTING);


    glColor3d(0.2,0.2,1);
    glPointSize(9.0);
    if(is_debug_draw_vertex==true)
    {
        glBegin(GL_POINTS);
        for(int k=0,N=mesh_current.number_of_vertices();k<N;++k)
        {
            const v3& p=mesh_current.vertex(k);
            glVertex3d(p.x(),p.y(),p.z());
        }
        glEnd();
    }

    std::vector<v3> p_index;
    std::vector<v3> translation_face;
    for(int k=0,N=mesh_current.number_of_vertices();k<N;++k)
        p_index.push_back(mesh_current.vertex(k)-nv[k]*L_text);
    for(int k=0,N=mesh_current.number_of_triangle();k<N;++k)
        translation_face.push_back(-L_text*np[k]);

    glColor3d(0,0,0);
    draw_index(p_index);
    glColor3d(1,0,0);
    draw_index_face(mesh_current,translation_face);
}

void debug_mesh::draw_index(const std::vector<proj::v3>& x)
{
    if(is_debug_vertex_index==false)
        return ;

    int N=x.size();
    for(int k=0;k<N;++k)
        p_widget->draw_text(x[k][0],x[k][1],x[k][2],QString::number(k),QFont("Times",15,QFont::Normal));
}

void debug_mesh::draw_index_face(const proj::mesh& mesh,const std::vector<v3>& translate)
{
    if(is_debug_face_index==false)
        return ;

    proj::v3 x_bar;
    int N=mesh.number_of_triangle();
    for(int k=0;k<N;++k)
    {
        x_bar=(mesh.vertex_of_polygon(k,0)+mesh.vertex_of_polygon(k,1)+mesh.vertex_of_polygon(k,2))/3.0+translate[k];
        p_widget->draw_text(x_bar[0],x_bar[1],x_bar[2],QString::number(k),QFont("Times",15,QFont::Normal));
    }
}

void debug_mesh::set_glwidget(glwidget *_p_widget)
{
    p_widget=_p_widget;
}

void debug_mesh::set_is_debug_mode(bool value)
{
    is_debug_mode=value;
}

void debug_mesh::set_is_debug_vertex_index(bool value)
{
    is_debug_vertex_index=value;
}

void debug_mesh::set_is_debug_face_index(bool value)
{
    is_debug_face_index=value;
}

void debug_mesh::set_is_debug_inverted_normal(bool value)
{
    is_debug_inverted_normal=value;
}
void debug_mesh::set_is_debug_vertex_point(bool value)
{
    is_debug_draw_vertex=value;
}


}
