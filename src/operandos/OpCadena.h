#ifndef OPCADENA_H
#define OPCADENA_H

#include "..\Operando.h"

///Clase que representa el tipo de datos Cadena.
class OpCadena : public Operando
{
    public:
        OpCadena();
        /// Constructor.
        /// @param nom Nombre del operando.
        OpCadena(std::string nom);
        /// Constructor
        /// @param nom Nombre del operando.
        /// @param val Valor con el que se quiere inicializar el operando.
        OpCadena(std::string nom, std::string val);
        /// función que implementa la plantilla de la clase base @see Operando.
        /// @return Cadena que representa el valor del operando.
        std::string getValue();
        /// función que retorna el valor convertido al tipo que le corresponde en C++.
        /// @return valor del operando convertido a cadena.
        std::string getTypeValue();
        /// función que implementa la plantilla de la clase base @see Operando.
        /// @return Cadena con el tipo del opernando.
        std::string getTipo();
        /// función que implementa la plantilla de la clase base @see Operando.
        /// @return Cadena con el nombre del operando.
        std::string getNombre();
        /// función estática que comprueba si una cadena contiene un valor del tipo correspondiente al Operando.
        /// @param val valor de cadena a comprobar.
        /// @return bool si el parámetro tiene un formato válido para la conversión.
        static bool isType(std::string val);
        /// método que implementa la plantilla de la clase base @see Operando.
        /// @param val Cadena con el nuevo valor del operando.
        void setValue(std::string val);
        virtual ~OpCadena();
    private:
        std::string valor;
        static const std::string TIPO;
        std::string nombre;
};

#endif // OPCADENA_H
