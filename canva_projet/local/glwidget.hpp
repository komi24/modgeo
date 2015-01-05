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

#ifndef GLWIDGET_HPP
#define GLWIDGET_HPP


#include <QtOpenGL/QGLWidget>
#include <QTime>
#include <navigator_tool.hpp>
#include <scene.hpp>


class glwidget : public QGLWidget
{

    Q_OBJECT

public:

    glwidget(QWidget *parent=0);
    ~glwidget();

    void set_wireframe();
    void set_filled();

    scene current_scene;

    void draw_text(double x,double y,double z,QString text,QFont font);

protected:
  void initializeGL();
  void paintGL();
  void resizeGL(int width, int height);
  void mousePressEvent(QMouseEvent *event);
  void mouseReleaseEvent(QMouseEvent *event);
  void mouseMoveEvent(QMouseEvent *event);
  void keyPressEvent(QKeyEvent *event);
  void timerEvent(QTimerEvent *event);



private:

  proj::navigator_tool nav;


  void print_help_start() const;
  void draw_pointer(proj::navigator_tool& nav) const;
  void draw_orientation(proj::navigator_tool& nav) const;
  void draw_camera_stat();

  void draw_fps();
  void draw_decorating_info();

  QTime t_timer;

  unsigned int compteur_temps;

};


#endif
