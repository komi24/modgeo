
#include <scene.hpp>

// #include <GL/glew.h>
#include <QString>
#include <QFont>
#include <glwidget.hpp>
#include <vector>


#include <opengl_drawer.hpp>
#include <cmath>
#include <debug_mesh.hpp>

#include <assert.h>

using namespace proj;



void scene::load_model()
{
    assert(p_widget!=NULL);
    assert(p_debug_mesh!=NULL);


    //*****************************************//
    // Generate mesh                           //
    //*****************************************//

    int Nx = 320, Ny = 32;
    double x,y;
    for(int i = 0; i<Nx; ++i)
    {
        x = (double)i/(double)(Nx-1);
        for(int j = 0; j<Ny; ++j)
        {
            y = (double)j/(double)(Ny-1);

            double z = 0;
            mesh_0.add_vertex(v3(x,y,z));
            mesh_0.add_texture(v2(x*5,y*5));
        }
    }

    for(int i = 0; i<Nx-1; ++i)
    {
        for(int j = 0; j<Ny-1; ++j)
        {
            mesh_0.add_triangle(i*Ny+j,i*Ny+j+1,(i+1)*Ny+j);
            mesh_0.add_triangle(i*Ny+j+1,(i+1)*Ny+j+1,(i+1)*Ny+j);
        }
    }
    mesh_0.compute_normal();

//    mesh_1.load_file("../data/dino_0.off");
    mesh_1.load_file("../data/dino_0.obj");
    mesh_1.compute_normal();
    mesh_1.auto_scale();
    mesh_1.scale(0.1,0.1,0.1);
    mesh_1 += v3(0.5,0.5,0.1);

    const std::string texture_path_0="../data/seamless_grass_texture.png";
    texture_id_0=0;
    texture_id_0=p_widget->bindTexture(QString(texture_path_0.c_str()),GL_TEXTURE_2D);
    if(texture_id_0==0)
        std::cout<<"Erreur chargement texture "<<texture_path_0<<std::endl;

    //*****************************************//
    // \Generate mesh                          //
    //*****************************************//

}

void scene::draw_scene()
{
    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);

    glColor3d(1,1,1);

    glBindTexture(GL_TEXTURE_2D,texture_id_0);
    opengl_drawer::draw(mesh_0);


    glColor3d(0,0.5,0.1);
    glBindTexture(GL_TEXTURE_2D,0);
    opengl_drawer::draw(mesh_1);
    
    
    //draw debug information if asked in the GUI
    p_debug_mesh->draw_debug(mesh_0);
}



scene::scene()
{

    p_widget=NULL;
    p_debug_mesh=NULL;

    texture_id_0=0;
}


void scene::set_glwidget(glwidget *p_widget_)
{
    p_widget=p_widget_;
}
void scene::set_debug_mesh(debug_mesh *p_debug_mesh_)
{
    p_debug_mesh=p_debug_mesh_;
}


void scene::manage_time(unsigned int temps)
{

}

void scene::simplification(){
    this->mesh_1.simplification();
}



