#include "guardado.h"

guardado::guardado()
{

    QFile file("datos.txt");

    if ( file.open( QFile::ReadOnly | QFile::Text ) ){
        string  line;
        string nombre = "";

        while (!file.atEnd() ) {
            line = file.readLine().toStdString();
            line.resize(line.length()-1);               //  para quitarle el salto de linea que queda en el string
            nombre = line;

            line = file.readLine().toStdString();
            line.resize(line.length()-1);
            usuarios[nombre].push_back(line);

            line = file.readLine().toStdString();
            line.resize(line.length()-1);
            usuarios[nombre].push_back(line);

            line = file.readLine().toStdString();
            line.resize(line.length()-1);
            usuarios[nombre].push_back(line);

            line = file.readLine().toStdString();
            line.resize(line.length()-1);
            usuarios[nombre].push_back(line);
            line = file.readLine().toStdString();
        }
        file.flush();
        file.close();
    }
}

bool guardado::registro(string nombre, string contra)
{
    //          for para evitar espacios vacios
    if ( nombre == "" && contra == "" ){
        return false;
    }
    //          for para evitar nombres repetidos
    for (auto &ite : usuarios){
        if ( ite.first == nombre)
            return false;
    }

    // fors para confirmar que se ingrese con letras permitidas para el nombre y contraseña
    for ( unsigned int i = 0; i< nombre.length(); i++ ){
        if ( ( 64<nombre[i] && nombre[i]<91 ) || ( 96<nombre[i] && nombre[i]<123 ) || ( 48<nombre[i] && nombre[i]<58 ) ){
            NULL;
        }

        else{
            return  false;
        }
    }

    for ( unsigned int i = 0; i< contra.length(); i++ ){
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


    QFile file("datos.txt");

    if ( file.open( QFile::WriteOnly | QFile::Append) ){
        QTextStream out (&file);
        out << QString::fromStdString(nombre)<< '\n';
        out << QString::fromStdString(contra)<< '\n';
        out << 100 << '\n';
        out << 0 << '\n';
        out << 1 << '\n';
    }
    file.close();
    return true;


}

bool guardado::ingreso(string nombre, string contra)
{
    if ( nombre == "" && contra == "" ){
        return false;
    }
    for ( auto &ite : usuarios ){        // for para recorrer la lista de ususarios
        if ( ite.first == nombre && ite.second.at(0) == contra ){
            usuario_actual = nombre;
            return true;
        }
    }
    return false;
}

void guardado::guardado_datos( string salud, string marc, string nivel )
{
    //      for para actualizar datos del usuario que guarda
    for ( auto &ite : usuarios ){        // for para recorrer la lista de ususarios
        if ( ite.first == usuario_actual ){
            ite.second.at(1) = salud;
            ite.second.at(2) = marc;
            ite.second.at(3) = nivel;
        }
    }

    QFile file("datos.txt");

    if ( file.open( QFile::WriteOnly | QFile::Text ) ){
        QTextStream out (&file);
        for ( auto ite : usuarios ){        // for para recorrer la lista de ususarios
            out << QString::fromStdString(ite.first)  << '\n'
                << QString::fromStdString(ite.second.at(0)) << '\n'
                << QString::fromStdString(ite.second.at(1)) << '\n'
                << QString::fromStdString(ite.second.at(2)) << '\n'
                << QString::fromStdString(ite.second.at(3)) << "\n;\n";
        }
    }
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







