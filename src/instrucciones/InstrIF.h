#ifndef INSTRIF_H
#define INSTRIF_H

#include "..\Instruccion.h"
#include "InstrGOTO.h"


/// Prototipo de la clase parser
class Parser;
/// Prototipo de la clase InstrGOTO
class InstrGOTO;

/// Clase que representa una instrucción IF con salto condicional.
class InstrIF : public Instruccion
{
    public:
        InstrIF();
        virtual ~InstrIF();
        /// Constructor
        /// @param a @see Operando de la condición lógica del if
        /// @param b @see Operando de la condición lógica del if
        /// @param opr @see Operador lógico de la condición del if
        /// @param jmp Etiqueta a la que se saltará en caso de ser falsa la condición. Apuntará a un ELSE o ENDIF según proceda. Se utilizará para crear una instrucción InstrGOTO que realizará el salto.
        /// @param p Puntero a un objeto de tipo @see Parser, para poder acceder a las etiquetas y puntero de ejecución y modificar su valor. Se utilizará para crear una instrucción InstrGOTO que realizará el salto.
        InstrIF(Operando* a, Operando* b, Operador* opr, std::string jmp, Parser* p);
        /// Constructor
        /// @param a @see Operando booleano con la condición del if
        /// @param jmp Etiqueta a la que se saltará en caso de ser falsa la condición. Apuntará a un ELSE o ENDIF según proceda. Se utilizará para crear una instrucción InstrGOTO que realizará el salto.
        /// @param p Puntero a un objeto de tipo @see Parser, para poder acceder a las etiquetas y puntero de ejecución y modificar su valor. Se utilizará para crear una instrucción InstrGOTO que realizará el salto.
        InstrIF(Operando* a, std::string jmp, Parser* p);
        /// Implementación de la plantilla definida en la clase base. Ejecuta la instrucción.
        bool ejecuta();
    protected:
    private:
        /// Puntero al primer @see Operando.
        Operando* opA;
        /// Puntero al segundo @see Operando. Puede ser NULL.
        Operando* opB;
        /// Puntero al @see Operador. Puede ser NULL.
        Operador* operacion;
        /// Puntero a la instrucción de salto a ejecutar en caso de que la condición sea falsa;
        InstrGOTO* iGoto;
};

#endif // INSTRIF_H
