
#include <Qt/QtGui>
#include <window.hpp>
#include <glwidget.hpp>
#include <window_mesh_debug.hpp>
#include <debug_mesh.hpp>

#include <ui_mainwindow.h>

#include <iostream>

#include <assert.h>

Window::Window(QWidget *parent)
  :QMainWindow(parent),ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  glWidget=NULL;
  glWidget = new glwidget;
  assert(glWidget!=NULL);

  p_debug_mesh=NULL;
  p_debug_mesh = new proj::debug_mesh;
  assert(p_debug_mesh!=NULL);

  glWidget->current_scene.set_debug_mesh(p_debug_mesh);
  p_debug_mesh->set_glwidget(glWidget);

  ui->layout_scene->addWidget(glWidget);

  window_debug=NULL;
  window_debug=new window_mesh_debug(this,glWidget,p_debug_mesh);
  assert(window_debug!=NULL);
 
  connect(ui->actionExit,SIGNAL(triggered()),this,SLOT(quit_window()));
  connect(ui->wireframe_checkbox,SIGNAL(stateChanged(int)),this,SLOT(set_wireframe(int)));
  connect(ui->debug_button,SIGNAL(clicked()),this,SLOT(debug_button_clicked()));
  connect(ui->simple_algo_button,SIGNAL(clicked()),this,SLOT(simple_algo_button_clicked()));
  connect(ui->optimized_algo_button,SIGNAL(clicked()),this,SLOT(optimized_algo_button_clicked()));
  connect(ui->slider_factor,SIGNAL(valueChanged(int)),ui->lcd_factor,SLOT(display(int)));
}

Window::~Window()
{
  if(ui!=0)
    {
      delete ui;
      ui=0;
    }
  if(window_debug!=0)
  {
      delete window_debug;
      window_debug=0;
  }
  if(p_debug_mesh!=NULL)
  {
      delete p_debug_mesh;
      p_debug_mesh=NULL;
  }

}

void Window::quit_window()
{
  std::cout<<"Exit window"<<std::endl;
  this->window()->close();
}

void Window::set_wireframe(int is_active)
{
    if(is_active==0)
        glWidget->set_filled();
    else
        glWidget->set_wireframe();
}
void Window::debug_button_clicked()
{
    window_debug->show();
}
void Window::simple_algo_button_clicked()
{
    window_debug->show();
}
void Window::optimized_algo_button_clicked()
{
    window_debug->show();
}
