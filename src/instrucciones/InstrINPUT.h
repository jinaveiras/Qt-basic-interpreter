#ifndef INSTRINPUT_H
#define INSTRINPUT_H

#include <iostream>
#include "..\Instruccion.h"
#include "..\Input.h"
#include "..\excepciones\EExecAborted.h"

/// Clase que representa una instrucción INPUT que solicita datos por pantalla y los asigna a un operando
class InstrINPUT : public Instruccion
{
    public:
        InstrINPUT();
        /// Constructor
        /// @param txt Puntero a Operando que representa el texto solicitando la entrada. @see Operando
        /// @param dest Puntero al Operando donde se almacenaran los datos recogidos. @see Operando
        /// @param i Puntero a la clase que se ocupa de gestionar la entrada de datos
        InstrINPUT(Operando *txt, Operando *dest, Input *i);
        virtual ~InstrINPUT();
        /// Implementación de la plantilla definida en la clase base. Ejecuta la instrucción.
        /// @throw EInvalidConversion Se lanza si no se puede almacenar lo recogido en el operando destino.
        bool ejecuta() throw (EInvalidConversion, EExecAborted);
    private:
        /// Puntero al operando con el texto.
        Operando *texto;
        /// Puntero al operando donde se almacenarán los datos recogidos.
        Operando *destino;
        /// Puntero a la clase que se ocupa de gestionar la entrada
        Input *input;
};


#endif // INSTRINPUT_H
