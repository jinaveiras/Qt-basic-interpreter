#ifndef SCANNER_H
#define SCANNER_H
#include <iostream>
#include <string>
#include <fstream>
#include "excepciones\EFileNotFound.h"
#include "excepciones\EInvalidKeyword.h"
#include "Parser.h"
#include "Input.h"
#include "Output.h"
#include "utils.h"
#include <QPlainTextEdit>
#include <QTextBlock>

using namespace std;

///    Clase que procesa el fichero de entrada con el programa en BASIC.

class Scanner
{
    public:
        virtual ~Scanner();
        /// @brief Contructor del Scanner
        /// @param ruta Nombre del fichero a procesar
        /// @param *i Puntero a la clase que se ocupará de gestionar la entrada
        /// @param *o Puntero a la clase que se ocupará de gestionar la salida
        Scanner(string ruta, Input *i, Output *o);
        /// @brief Contructor del Scanner
        /// @param *t Puntero a un contenedor de las instrucciones del programa. En este caso del tipo QPlainTextEdit @see QPlainTextEdit
        /// @param *i Puntero a la clase que se ocupará de gestionar la entrada
        /// @param *o Puntero a la clase que se ocupará de gestionar la salida
        Scanner(QPlainTextEdit *t, Input *i, Output *o);
        /// @brief Método que escanea el fichero
        /// @throw EFileNotFound Se lanza si no existe el fichero de entrada.
        /// @throw EInvalidKeyword Se lanza si no se reconoce la instrucción.
        /// @return True si el proceso de parseado a terminado correctamente, falso en caso contrario.
        bool scan() throw (EFileNotFound, EInvalidKeyword);
        /// Ejecuta las instrucciones del programa, previo parseado.
        void ejecuta();
    private:
        ///
        QPlainTextEdit *prog;
        /// Objeto que se ocupará del parseado del programa.
        Parser *p;
        /// Ruta del fichero que contiene el programa a interpretar
        string rutaProg;
        /// Puntero a la clase que se ocupa de gestionar la entrada de datos
        Input *input;
        /// Puntero a la clase que se ocupa de gestionar la salida de datos.
        Output *output;
        /// Procedimiento que se ocupa de enviar cada línea del programa al parser.
        /// @param linea Línea leída del fichero del programa.
        void procLinea(string linea);
        /// Procedimiento que inicializa atributos del objeto
        void inicializa(Input *i, Output *o);
};

#endif // SCANNER_H
