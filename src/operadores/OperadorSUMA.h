#ifndef OPERADORSUMA_H
#define OPERADORSUMA_H

#include "..\Operador.h"

/// Clase que representa el operador de suma
class OperadorSUMA : public Operador
{
    public:
        OperadorSUMA();
        virtual ~OperadorSUMA();
        /// función que implementa la plantilla @see Instruccion
        /// @param opA Puntero al primer @see Operando
        /// @param opB Puntero al segundo @see Operando
        /// @return cadena con el valor del resutado de ejecutar el operador sobre los operandos.
        std::string ejecuta(Operando* opA, Operando* opB);
        /// función que devuelve el símbolo que identifica el operador.
        /// @return string con el símbolo.
        std::string getSimbolo();
    protected:
    private:
        /// atributo de clase que representa el símbolo del operador.
        static const std::string SIMBOLO;
};

#endif // OPERADORSUMA_H
