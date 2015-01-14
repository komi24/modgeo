
#ifndef SCENE_HPP
#define SCENE_HPP

#include <matrix3.hpp>
#include <v3.hpp>
#include <mesh.hpp>

#include <vector>

class glwidget;

namespace proj
{
class debug_mesh;
}

class scene
{

public:

    scene();

    /** \brief  simplification */
    void simplification();

    /** \brief Method called only once at the beginning (load off files ...) */
    void load_model();
    /** \brief Method called at every frame */
    void draw_scene();

    void manage_time(unsigned int temps);

    //set glwidget pointer
    void set_glwidget(glwidget *p_widget);

    //set debug_mesh pointer
    void set_debug_mesh(proj::debug_mesh *p_debug_mesh);

private:


    proj::mesh mesh_0;
    unsigned int texture_id_0;

    proj::mesh mesh_1;

    glwidget *p_widget;
    proj::debug_mesh *p_debug_mesh;

};

#endif
