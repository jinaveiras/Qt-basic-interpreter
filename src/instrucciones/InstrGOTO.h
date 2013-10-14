#ifndef INSTRGOTO_H
#define INSTRGOTO_H

#include "..\Parser.h"
#include "..\Instruccion.h"

using namespace std;

/// Prototipo de la clase Parser
class Parser;

/// Clase que representa una instrucción GOTO de salto incondicional.
class InstrGOTO : public Instruccion
{
    public:
        InstrGOTO();
        /// Constructor
        /// @param nEtiq Es la etiqueta a la que se tiene que hacer el salto.
        /// @param p Puntero a un objeto de tipo @see Parser, para poder acceder a las etiquetas y puntero de ejecución y modificar su valor.
        InstrGOTO(const string nEtiq, Parser* p);
        virtual ~InstrGOTO();
        /// Implementación de la plantilla definida en la clase base. Ejecuta la instrucción.
        bool ejecuta();
    private:
        /// Almacena el nombre de la etiqueta a la que se va a saltar cuando se ejecute la instrucción
        string nombreEtiq;
        /// Puntero al parser
        Parser* prsr;
};

#endif // INSTRGOTO_H
