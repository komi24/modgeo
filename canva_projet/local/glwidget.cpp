
#include <glwidget.hpp>

#include <matrix3.hpp>
#include <matrix4.hpp>

#include <GL/glu.h>
#include <Qt/QtOpenGL>
#include <QtOpenGL/QGLWidget>




glwidget::glwidget(QWidget *parent)
  : QGLWidget(parent)
{
    QWidget::setFocusPolicy(Qt::StrongFocus);
    startTimer(25);

    print_help_start();
    current_scene.set_glwidget(this);
    compteur_temps = 0;
}

glwidget::~glwidget()
{
}

void glwidget::print_help_start() const
{
    std::cout<<"**RUN**\n"<<std::endl;
    std::cout<<"Navigation with keys:\n\n"<<std::endl;
    std::cout<<"==========================\n"<<std::endl;
    std::cout<<"Space Displacement"<<std::endl;
    std::cout<<"  z    r"<<std::endl;
    std::cout<<"q s d  f\n"<<std::endl;
    std::cout<<"and mouse (/shift) with drag & drop\n"<<std::endl;
    std::cout<<"W: wireframe mode"<<std::endl;
    std::cout<<"F: filled mode"<<std::endl;
    std::cout<<"Q: exit"<<std::endl;
    std::cout<<"==========================\n"<<std::endl;
}

void glwidget::initializeGL()
{
    qglClearColor(QColor(255,255,255));
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glFrontFace( GL_CW ) ;
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT,GL_NICEST);

    glEnable(GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_COLOR_MATERIAL);


    try
    {
        current_scene.load_model();
    }
    catch(std::string e)
    {
        std::cout<<"************************************************"<<std::endl;
        std::cout<<"Exception: "<<e<<std::endl;
        std::cout<<"************************************************"<<std::endl;
        exit(1);
    }
}

void glwidget::paintGL()
{
    //vieport (all screen)
    glViewport (0, 0, nav.screen_size_x(),nav.screen_size_y());
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity ();
    std::vector<double> proj_param=nav.projection_param();
    glFrustum(proj_param[0], -proj_param[0], proj_param[1], -proj_param[1], proj_param[2], proj_param[3]);


    //Modelview
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslated(0,0,static_cast<GLdouble>(nav.dist_cam())); //zoom
    std::vector<double> m=proj::matrix4(nav.camera_orientation()).to_vector();
    glMultMatrixd(&m[0]); //rotation

    //translation
    proj::v3 tr=nav.camera_translation();
    glTranslated(static_cast<GLdouble>(tr[0]),static_cast<GLdouble>(tr[1]),static_cast<GLdouble>(tr[2]));


    //draw scene
    current_scene.draw_scene();

    //draw info, fps, ...
    draw_decorating_info();



    //redraw
    glFlush ();

}

void glwidget::draw_decorating_info()
{
    // draw_pointer
    draw_pointer(nav);
    // draw orientation
    draw_orientation(nav);


    //error OpenGL_drawer_2
    GLenum errCode;
    const GLubyte *errString;
    if((errCode=glGetError()) != GL_NO_ERROR)
      {
        errString = gluErrorString(errCode);
        std::cout<<"OPENGL ERROR : "<<errString<<std::endl;
        //exit(-2);
      }


    //update fps
    nav.increase_frame_number();
    nav.time()=t_timer.elapsed();
    if(nav.delta_time()>1000)
        nav.update_fps();


    //draw fps
    draw_fps();


    //draw bottom right zoom
    draw_camera_stat();
}


void glwidget::draw_pointer(proj::navigator_tool& nav) const
{

    glPushMatrix();
    glLoadIdentity();

    glTranslatef(0,0,GLfloat(nav.dist_cam())); //zoom
    std::vector<double> m=proj::matrix4(nav.camera_orientation()).to_vector();
    glMultMatrixd(&m[0]); //rotation

    //local basis
    double L=0.01;

    glDisable(GL_LIGHTING);
    glBegin(GL_LINES);
    glColor3d(1,0,0);
    glVertex3d(-L,0,0);
    glVertex3d(L,0,0);
    glColor3d(0,1,0);
    glVertex3d(0,-L,0);
    glVertex3d(0,L,0);
    glColor3d(0,0,1);
    glVertex3d(0,0,-L);
    glVertex3d(0,0,L);
    glEnd();

    glPopMatrix();

}

void glwidget::draw_orientation(proj::navigator_tool& nav) const
{
    glDisable(GL_LIGHTING);
    //rotation
    glClear(GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity ();
    glOrtho(-1,1,1,-1,0.1,10.0);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glTranslated(0.78,0.78,-1);
    std::vector<double> m=proj::matrix4(nav.camera_orientation()).to_vector();
    // rotation
    glMultMatrixd(&m[0]);

    double L=0.2;
    glBegin(GL_LINES);
    glColor3d(1,0,0);
    glVertex3d(0,0,0);
    glVertex3d(L,0,0);
    glColor3d(0,1,0);
    glVertex3d(0,0,0);
    glVertex3d(0,L,0);
    glColor3d(0,0,1);
    glVertex3d(0,0,0);
    glVertex3d(0,0,L);
    glEnd();
    //pop matrices
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

void glwidget::resizeGL(int width, int height)
{
    nav.screen_size_x()=width;nav.screen_size_y()=height;glViewport(0,0, width, height);
}

void glwidget::mousePressEvent(QMouseEvent *event)
{
    nav.x_previous()=event->x();
    nav.y_previous()=event->y();


    updateGL();
}

void glwidget::mouseReleaseEvent(QMouseEvent *)
{

    updateGL();
}

void glwidget::mouseMoveEvent(QMouseEvent *event)
{
    int x=event->x();
    int y=event->y();


    int shift_pressed = (event->modifiers() & Qt::ShiftModifier);
    if (!shift_pressed && (event->buttons() & Qt::LeftButton) )
        nav.trackball_rotate(x,y);
    else if (!shift_pressed && (event->buttons() & Qt::RightButton))
        nav.trackball_zoom(y);

    double dL=0.0001*(1+10*abs(nav.dist_cam()));
    if( shift_pressed && (event->buttons() & Qt::LeftButton) )
    {
        nav.go_up(dL*(y-nav.y_previous()));
        nav.go_right(-dL*(x-nav.x_previous()));
    }
    if( shift_pressed && (event->buttons() & Qt::RightButton) )
        nav.go_forward(5*dL*(y-nav.y_previous()));


    nav.x_previous()=x;
    nav.y_previous()=y;

    updateGL();

}

void glwidget::keyPressEvent(QKeyEvent *event)
{
    QString k=event->text();


    int current=event->key();
    Qt::KeyboardModifiers mod=event->modifiers();

    if( (mod&Qt::ShiftModifier)!=0 && (current==Qt::Key_Q) )
    {
        std::cout<<"\n[EXIT OK]\n\n"<<std::endl;
        this->window()->close();
    }



    //MOVE
    double dL=0.01*(1+10*abs(nav.dist_cam()));//move camera

    // move forward
    if( (mod==0) && (current==Qt::Key_Z) )
        nav.go_forward(dL);
    // move backward
    if( (mod==0) && current==Qt::Key_S)
        nav.go_forward(-dL);
    // move left
    if( (mod==0) && (current==Qt::Key_Q) )
        nav.go_right(-dL);
    // move right
    if( (mod==0) && current==Qt::Key_D)
        nav.go_right(dL);
    // move up
    if( (mod==0) && current==Qt::Key_R)
        nav.go_up(dL);
    // move down
    if( (mod==0) && current==Qt::Key_F)
        nav.go_up(-dL);



    QGLWidget::keyPressEvent(event);
    updateGL();
}

void glwidget::timerEvent(QTimerEvent *event)
{

    compteur_temps=(compteur_temps+1)%1000;
    current_scene.manage_time(compteur_temps);

    event->accept();
    updateGL();
}

void glwidget::set_wireframe()
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    updateGL();
}
void glwidget::set_filled()
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    updateGL();
}



void glwidget::draw_fps()
{
    glDisable(GL_DEPTH_TEST);

    int int_fps=int(nav.fps());
    int deci_fps=int(10*(nav.fps()-int_fps));
    double truncated_fps=int_fps+double(deci_fps)/10.0;

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity ();
    glOrtho(-1,1,1,-1,0.1,10.0);
    glMatrixMode(GL_MODELVIEW);

    glColor3d(0.2,0.2,0.5);
    glPushMatrix();
    glLoadIdentity();

    QString str_fps=QString::number(truncated_fps,'g',3)+" fps";
    //tr(truncated_fps);
    renderText(-0.93,-0.88,-1,str_fps,QFont("Times",15,QFont::Bold));


    //pop matrices
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

    glEnable(GL_DEPTH_TEST);
}

void glwidget::draw_camera_stat()
{
    double dist=fabs(nav.dist_cam());

    if(dist<1.0)
        dist=double(int(100*(dist-int(dist))))/100.0;
    else if(dist<10 && dist>=1)
        dist = int(dist)+double(int(10*(dist-int(dist))))/10.0;
    else if(dist>=10)
        dist=int(dist);


    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity ();
    glOrtho(-1,1,1,-1,0.1,10.0);
    glMatrixMode(GL_MODELVIEW);


    glPushMatrix();
    glLoadIdentity();
    glColor3d(0,0,0);
    renderText(0.75,0.55,-1.25,QString("dist: ")+QString::number(dist,'g',3),QFont("Times",10));
    glPopMatrix();

    glColor3d(1,1,1);


    //pop matrices
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

void glwidget::draw_text(double x,double y,double z,QString text,QFont font)
{
    renderText(x,y,z,text,font);
}
