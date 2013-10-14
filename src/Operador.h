#ifndef OPERADOR_H
#define OPERADOR_H

#include <string>
#include <iostream>

#include "excepciones\EMalformedBlockError.h"

// Operandos
#include "Operando.h"
#include "operandos\OpEntero.h"
#include "operandos\OpFlotante.h"
#include "operandos\OpCadena.h"
#include "operandos\OpBooleano.h"

/// Clase base para los operadores soportados
class Operador
{
    public:
        /// plantilla para la función que ejecuta la operación correspondiente al operador.
        /// @param opA Puntero a @see Operando
        /// @param opB Puntero a @see Operando
        /// @return Cadena con el resultado de la operación.
        virtual std::string ejecuta(Operando* opA, Operando* opB)=0;
        /// función que devuelve el símbolo que identifica el operador.
        /// @return string con el símbolo.
        virtual std::string getSimbolo()=0;
};

#endif // OPERADOR_H
