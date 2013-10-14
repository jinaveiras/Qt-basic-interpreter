#ifndef EFILENOTFOUND_H
#define EFILENOTFOUND_H

#include <string>
#include <stdexcept>

using namespace std;

/// Excepción que se lanza cuando no se encuentra un fichero.
class EFileNotFound : public invalid_argument
{
    public:
        EFileNotFound(string msg) : invalid_argument("Fichero no encontrado: "+msg) {};
    private:
};

#endif // EFILENOTFOUND_H
