
#ifndef WINDOW_MESH_DEBUG_HPP
#define WINDOW_MESH_DEBUG_HPP

#include <iostream>
#include <QtGui/QMainWindow>
#include <QtGui/QDialog>
#include <QtGui/QColorDialog>

#include <glwidget.hpp>

namespace Ui
{
    class mesh_debug;
}
class glwidget;

namespace proj
{
class debug_mesh;
}


class window_mesh_debug : public QDialog
{
    Q_OBJECT

public:

    window_mesh_debug(QMainWindow *parent=0,glwidget *wid=0,proj::debug_mesh *p_debug_mesh=0);
    ~window_mesh_debug();

private:

     Ui::mesh_debug *ui;
     glwidget *glWidget;
     proj::debug_mesh *p_debug_mesh;

 private slots:
     void accept();
     void reject();

     void debug_mode_button_clicked(bool is_clicked);

     void vertex_index_button_clicked(bool is_clicked);
     void face_index_button_clicked(bool is_clicked);
     void inverted_normal_button_clicked(bool is_clicked);
     void vertex_show_button_clicked(bool is_clicked);

};


#endif
