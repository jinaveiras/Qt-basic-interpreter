#ifndef INSTRUCCION_H
#define INSTRUCCION_H

#include "Operando.h"

/// Clase abstracta que representa una instrucción del programa
class Instruccion
{
    public:
        /// plantilla para la función que ejecuta la instrucción
        /// @return bool Retorna True si la ejecución ha sido correcta. False en caso contrario.
        virtual bool ejecuta() = 0;
};

#endif // INSTRUCCION_H
