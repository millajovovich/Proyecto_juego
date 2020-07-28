#include "guardado.h"

guardado::guardado()
{
    ifstream entrada;
    entrada.open("datos.txt");

    string nombre = "", linea;

    //          while para obtener datos de cada usuario
    while ( !entrada.eof() ){
        getline(entrada, linea);
        nombre = linea;

        getline(entrada, linea);
        usuarios[nombre].push_back(linea);

        getline(entrada, linea);
        usuarios[nombre].push_back(linea);

        getline(entrada, linea);
        usuarios[nombre].push_back(linea);

        getline(entrada, linea);
        usuarios[nombre].push_back(linea);
        getline(entrada, linea);
    }
}

bool guardado::registro(string nombre, string contra){

    // fors para confirmar que se ingrese con letras permitidas para el nombre y contraseña
    for (unsigned int i = 0; i< nombre.length(); i++ ){
        if ( ( 64<nombre[i] && nombre[i]<91 ) || ( 96<nombre[i] && nombre[i]<123 ) || ( 48<nombre[i] && nombre[i]<58 ) ){
            NULL;
        }

        else{
            return  false;
        }
    }

    for (unsigned int i = 0; i< contra.length(); i++ ){
        if ( ( 64<contra[i] && contra[i]<91 ) || ( 96<contra[i] && contra[i]<123 ) || ( 48<contra[i] && contra[i]<58 ) ){
            NULL;
        }

        else{
            return  false;
        }
    }
    usuarios[nombre].push_back(contra);                 // agrego contraseña al mapa
    usuarios[nombre].push_back("100");                  // agrego salud al mapa
    usuarios[nombre].push_back("0");                    // agrego marcador al mapa
    usuarios[nombre].push_back("1");                    // agrego nivel al mapa
    usuario_actual = nombre;
    return true;
}

bool guardado::ingreso(string nombre, string contra)
{
    for ( auto &ite : usuarios ){        // for para recorrer la lista de ususarios
        if ( ite.first == nombre && ite.second.at(0) == contra ){
            usuario_actual = nombre;
            return true;
        }
    }
    return false;
}

void guardado::guardado_datos(  string marc, string salud, string nivel )
{
    ofstream salida;
    salida.open("datos.txt");

    // guardado de datos de jugador actual
    for ( auto &ite : usuarios ){        // for para recorrer la lista de ususarios
        if ( ite.first == usuario_actual ){
            ite.second.at(1) = salud;
            ite.second.at(2) = marc;
            ite.second.at(3) = nivel;
        }
    }


    // for para colocar toda la info de los usuarios en archivo
    for ( auto ite : usuarios ){        // for para recorrer la lista de ususarios
        salida<< ite.first << '\n' << ite.second.at(0) << '\n' << ite.second.at(1) << '\n' << ite.second.at(2) << '\n'
              << ite.second.at(3) << "\n;\n";
    }

    salida.close();
}

void guardado::obt_datos(int *salud, int *marc, int *nivel)
{
    for ( auto ite : usuarios ){        // for para recorrer la lista de ususarios
        if ( ite.first == usuario_actual ){
            *salud = stoi(ite.second.at(1));
            *marc  = stoi(ite.second.at(2));
            *nivel = stoi(ite.second.at(3));
        }
    }
}   //          cambiar los  qstring por std     .toStdString()







