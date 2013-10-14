#ifndef EINVALIDKEYWORD_H
#define EINVALIDKEYWORD_H

#include <string>
#include <stdexcept>

using namespace std;

/// Excepción que se lanza cuando se encuentra una palabra no válida.
class EInvalidKeyword : public invalid_argument
{
    public:
        EInvalidKeyword(string msg) : invalid_argument("Palabra clave no reconocida: "+msg) {};
};

/// Excepción que se lanza cuando se encuentra una instrucción no válida.
class EInvalidInstr : public EInvalidKeyword
{
    public:
        EInvalidInstr(string msg) : EInvalidKeyword(msg) {};
};

/// Excepción que se lanza cuando se pretende operar sobre un operando pero no ha sido inicializado.
class EOperandoNoInicializado : public invalid_argument
{
    public:
        EOperandoNoInicializado(string msg) : invalid_argument(msg) {};
};

/// Excepción que se lanza cuando no se puede llevar a cabo una conversión a un tipo.
class EInvalidConversion : public invalid_argument
{
    public:
        EInvalidConversion(string origen, string destino) : invalid_argument(origen+" no es un "+destino+" valido") {};
};

#endif // EINVALIDKEYWORD_H
