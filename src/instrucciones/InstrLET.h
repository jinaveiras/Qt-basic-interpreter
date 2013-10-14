#ifndef INSTLET_H
#define INSTLET_H

#include <iostream>
#include <vector>
#include "..\Instruccion.h"
#include "..\Operador.h"

using namespace std;

/// Clase que representa una instrucción LET que asigna a un operando otro valor, bien cogido de otro operando, bien como resultado de aplicar un operador sobre dos operandos.
class InstrLET : public Instruccion
{
    public:
        InstrLET();
        /// Constructor
        /// @param dest Puntero al @see Operando en el que se quiere almacenar el valor
        /// @param a Puntero al primer @see Operando
        /// @param b Puntero al segundo @see Operando
        /// @param op Puntero al @see Operador a ejecutar sobre los parámetros anteriores.
        InstrLET(Operando* dest, Operando* a, Operando* b, Operador *op);
        /// Constructor
        /// @param dest Puntero al @see Operando en el que se quiere almacenar el valor
        /// @param a Puntero al @see Operando del que se tomará el valor.
        InstrLET(Operando* dest, Operando* a);
        virtual ~InstrLET();
        /// Implementación de la plantilla definida en la clase base. Ejecuta la instrucción.
        bool ejecuta();
    private:
        /// Puntero al @see Operando en el que se quiere almacenar el valor
        Operando* destino;
        /// Puntero al primer @see Operando
        Operando* opA;
        /// Puntero al segundo @see Operando. Puede ser NULL.
        Operando* opB;
        /// Puntero al operador @see Operador. Puede ser NULL.
        Operador* operador;
};

#endif // INSTLET_H
