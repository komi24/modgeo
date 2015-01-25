#ifndef VERTEXPAIR_H
#define VERTEXPAIR_H

class vertexpair
{
public:
    vertexpair(){}

    vertexpair(int vertex1, int vertex2, double dist){
        vert1=vertex1;
        vert2=vertex2;
        d=dist;
    }

    int vert1;
    int vert2;
    double d;

    bool operator<(const vertexpair& vertex2) const {
        return d > vertex2.d;
        // Alucinas pepinillos:
        // con < salen los mas grandes pero ordenados bien (de menos a mas)
        // con > salen los mas pequeños pero ordenados mal (de mas a menos)
        // bueno, con > estoy viendo cosas raras...
    }

};



#endif // VERTEXPAIR_H
