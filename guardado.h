#ifndef GUARDADO_H
#define GUARDADO_H

#include <iostream>
#include <QFile>
#include <QTextStream>
#include <vector>
#include <map>

using namespace std;

class guardado
{
    string usuario_actual;                         // para saber que usuario estaen sesion
    map < string, vector <string> > usuarios;

public:
    guardado();
    bool registro(string nombre, string contra);        // para retornar si es valido o no el registro
    bool ingreso(string nombre, string contra);         // ingreso de usuario

    void guardado_datos( string marc, string salud, string nivel );
    void obt_datos( int *salud, int *marc, int *nivel );

};

#endif // GUARDADO_H
