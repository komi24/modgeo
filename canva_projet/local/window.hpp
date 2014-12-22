
#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <QtGui/QMainWindow>

namespace Ui
{
  class MainWindow;
}
class glwidget;
class window_mesh_debug;

namespace proj
{
    class debug_mesh;
}

class Window : public QMainWindow
{
  Q_OBJECT

  public:
  Window(QWidget *parent=0);
  ~Window();

  glwidget *glWidget;
  window_mesh_debug *window_debug;


  private:

  Ui::MainWindow *ui;
  proj::debug_mesh *p_debug_mesh;



private slots:
  void quit_window();
  void set_wireframe(int is_active);
  void debug_button_clicked();
};

#endif
