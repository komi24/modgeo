
#include <QtGui/QApplication>
#include <window.hpp>

#include <exception_proj.hpp>

int main(int argc,char *argv[])
{
    try
    {
        std::cout<<"saluut "<<std::endl;
        QApplication app(argc,argv);
        Window window;
        window.show();

        return app.exec();
    }
    catch(proj::exception_proj e)
    {
        std::cout<<std::endl;
        std::cout<<"==========================================================="<<std::endl;
        std::cout<<"Exception recuperee dans fichier "<<__FILE__<<std::endl;
        std::cout<<e.info()<<std::endl;
        std::cout<<"==========================================================="<<std::endl;
    }

}
