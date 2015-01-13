
#include <window_mesh_debug.hpp>

#include <Qt/QtGui>


#include <glwidget.hpp>
#include <debug_mesh.hpp>


#include "ui_mesh_debug.h"


window_mesh_debug::window_mesh_debug(QMainWindow *parent,glwidget *wid,proj::debug_mesh *p_debug_mesh_)
    :QDialog(parent),ui(new Ui::mesh_debug),glWidget(wid),p_debug_mesh(p_debug_mesh_)
{
        ui->setupUi(this);

        connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
        connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

        connect(ui->debug_mode_button,SIGNAL(clicked(bool)),this,SLOT(debug_mode_button_clicked(bool)));

        connect(ui->vertex_index_button,SIGNAL(clicked(bool)),this,SLOT(vertex_index_button_clicked(bool)));
        connect(ui->face_index_button,SIGNAL(clicked(bool)),this,SLOT(face_index_button_clicked(bool)));
        connect(ui->inverted_normal_button,SIGNAL(clicked(bool)),this,SLOT(inverted_normal_button_clicked(bool)));
        connect(ui->vertex_show_button,SIGNAL(clicked(bool)),this,SLOT(vertex_show_button_clicked(bool)));

        debug_mode_button_clicked(false);
}

window_mesh_debug::~window_mesh_debug()
{
    if(ui!=0)
    {
        delete ui;
        ui=0;
    }
}

void window_mesh_debug::accept()
{
    done(0);
}

void window_mesh_debug::reject()
{
    done(0);
}

void window_mesh_debug::debug_mode_button_clicked(bool is_clicked)
{
    if(is_clicked==true)
    {
        p_debug_mesh->set_is_debug_mode(true);

        ui->vertex_index_button->setEnabled(true);
        ui->face_index_button->setEnabled(true);
        ui->inverted_normal_button->setEnabled(true);
        ui->vertex_show_button->setEnabled(true);
    }
    else
    {
        p_debug_mesh->set_is_debug_mode(false);

        ui->vertex_index_button->setEnabled(false);
        ui->face_index_button->setEnabled(false);
        ui->inverted_normal_button->setEnabled(false);
        ui->vertex_show_button->setEnabled(false);
    }
}

void window_mesh_debug::vertex_index_button_clicked(bool is_clicked)
{
    if(is_clicked==true)
        p_debug_mesh->set_is_debug_vertex_index(true);
    else
        p_debug_mesh->set_is_debug_vertex_index(false);
}

void window_mesh_debug::face_index_button_clicked(bool is_clicked)
{
    if(is_clicked==true)
        p_debug_mesh->set_is_debug_face_index(true);
    else
        p_debug_mesh->set_is_debug_face_index(false);
}

void window_mesh_debug::inverted_normal_button_clicked(bool is_clicked)
{
    if(is_clicked==true)
        p_debug_mesh->set_is_debug_inverted_normal(true);
    else
        p_debug_mesh->set_is_debug_inverted_normal(false);
}

void window_mesh_debug::vertex_show_button_clicked(bool is_clicked)
{
    if(is_clicked==true)
        p_debug_mesh->set_is_debug_vertex_point(true);
    else
        p_debug_mesh->set_is_debug_vertex_point(false);
}
