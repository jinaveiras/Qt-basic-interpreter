#ifndef OPBOOLEANO_H
#define OPBOOLEANO_H

#include "..\Operando.h"

///Clase que representa el tipo de datos Booleano.
class OpBooleano : public Operando
{
    public:
        OpBooleano();
        /// Constructor.
        /// @param nom Nombre del operando.
        OpBooleano(std::string nom);
        /// Constructor
        /// @param nom Nombre del operando.
        /// @param val Valor con el que se quiere inicializar el operando.
        OpBooleano(std::string nom, std::string val);
        /// función que implementa la plantilla de la clase base @see Operando.
        /// @return Cadena que representa el valor del operando.
        std::string getValue();
        /// función que retorna el valor convertido al tipo que le corresponde en C++.
        /// @return valor del operando convertido a bool.
        bool getTypeValue();
        /// función que implementa la plantilla de la clase base @see Operando.
        /// @return Cadena con el nombre del opernando.
        std::string getNombre();
        /// función estática que convierte un valor del tipo correspondiente en C++ al valor del Operando.
        /// @param x valor bool a convertir.
        /// @return cadena con el valor del parametro convertido al valor del operando.
        static std::string boolToStr(bool x);
        /// función que implementa la plantilla de la clase base @see Operando.
        /// @return Cadena con el tipo del operando.
        std::string getTipo();
        /// función estática que comprueba si una cadena contiene un valor del tipo correspondiente al Operando.
        /// @param val valor de cadena a comprobar.
        /// @return bool si el parámetro tiene un formato válido para la conversión.
        static bool isType(std::string val);
        /// método que implementa la plantilla de la clase base @see Operando.
        /// @param val Cadena con el nuevo valor del operando.
        /// @throw @see EInvalidConversion se lanza en caso de que el parametro proporcionado no sea convertible al tipo necesitado por el operando.
        void setValue(std::string val) throw (EInvalidConversion);
        virtual ~OpBooleano();
    private:
        /// Cadena que almacena el valor del operando.
        std::string valor;
        /// Atributo de clase que almacena el tipo del operando.
        static const std::string TIPO;
        /// Cadena que almacena el nombre del operando.
        std::string nombre;
};

#endif // OPBOOLEANO_H
