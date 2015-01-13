
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

std::vector<int> updateConnectivity(std::vector<int> v, int m, int n)
{

    std::vector<int> w;
    int a, b, c;
    bool am, an, bm, bn, cm, cn;

    for (std::size_t i=0;i<v.size();i=i+3) {
        a = v[i];
        b = v[i+1]; // 3 vertices from the face
        c = v[i+2];

        if (a==m) am = true; else am=false;
        if (a==n) an = true; else an=false;
        if (b==m) bm = true; else bm=false;
        if (b==n) bn = true; else bn=false;
        if (c==m) cm = true; else cm=false;
        if (c==n) cn = true; else cn=false;

        if(!am && !an && !bm && !bn && !cm && !cn) {
            // No vertex is changing, we do not modify this face
            w.push_back(a);
            w.push_back(b);
            w.push_back(c);
        } else if ((am || bm || cm) && (an || bn || cn)) {
            // The two vertices are in the triangle, we do not include the face in the new mesh
        } else {
            // One vertex will change
            if(am || an){
                w.push_back(m);
                w.push_back(b);
                w.push_back(c);
            } else if(bm || bn){
                w.push_back(a);
                w.push_back(m);
                w.push_back(c);
            } else {
                w.push_back(a);
                w.push_back(b);
                w.push_back(m);
            }
        }

    }

    return w;
}

void Window::simple_algo_button_clicked()
{

    char buffer[80];
    std::vector<int> v;

    v.push_back(1);v.push_back(2);v.push_back(7); // Face 1
    v.push_back(2);v.push_back(7);v.push_back(3); // Face 2
    v.push_back(3);v.push_back(7);v.push_back(8); // Face 3
    v.push_back(3);v.push_back(4);v.push_back(8); // Face 4
    v.push_back(4);v.push_back(5);v.push_back(8); // Face 5
    v.push_back(5);v.push_back(8);v.push_back(6); // Face 6
    v.push_back(6);v.push_back(7);v.push_back(8); // Face 7
    v.push_back(1);v.push_back(7);v.push_back(6); // Face 8

    v = updateConnectivity(v, 2, 3);

    for(int i = 0; i < v.size(); i++) {
        if(i%3==0)std::cout << "" << std::endl;
        sprintf(buffer, "%d", v[i]);
        std::cout << buffer << std::endl;
    }


    window_debug->show();
}
void Window::optimized_algo_button_clicked()
{
    window_debug->show();
}
