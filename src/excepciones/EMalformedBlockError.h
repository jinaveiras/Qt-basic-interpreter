#ifndef EMALFORMEDBLOCKERROR_H
#define EMALFORMEDBLOCKERROR_H

#include <string>
#include <stdexcept>

using namespace std;

/// Excepción
/// @exception EMalformedBlockError Excepción que se lanza cuando un bloque del programa no tiene la estructura esperada.
class EMalformedBlockError : public invalid_argument
{
    public:
        EMalformedBlockError(string msg) : invalid_argument(msg) {};
};

#endif // EMALFORMEDBLOCKERROR_H
