#ifndef UTILS_H
#define UTILS_H

#include <cstdlib>
#include <string>
#include <sstream>

using namespace std;

class Utils
{
    public:
        Utils();
        /// función estática que elimina caracteres especiales y espacios en blanco del principio y el fin de una cadena
        /// @param cad Cadena de la que se quieren eliminar dichos caracteres.
        /// @return la cadena sin los caracteres.
        static string trim(string cad);
        /// función estática que elimina caracteres especificados del principio y el fin de una cadena
        /// @param cad Cadena de la que se quieren eliminar dichos caracteres.
        /// @param caracteres Cadena con los caracteres que se quieren eliminar de la cadena.
        /// @return la cadena sin los caracteres.
        static string trim(string cad, string caracteres);
    protected:
    private:
};

#endif // UTILS_H
