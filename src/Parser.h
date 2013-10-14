#ifndef PARSER_H
#define PARSER_H
/// @def MIDEBUG habilita o deshabilita la salida de depuración del programa. Si se comenta el define, se deshabilita.
//#define MIDEBUG

#include <iostream>
#include <set>
#include <vector>
#include <stack>
#include <map>
#include <string>
#include "Utils.h"

#include "Input.h"
#include "Output.h"

// Excepciones
#include "excepciones\EMalformedBlockError.h"
#include "excepciones\EInvalidKeyword.h"
#include "excepciones\EExecAborted.h"

// Instrucciones
#include "Instruccion.h"
#include "instrucciones\InstrPRINT.h"
#include "instrucciones\InstrGOTO.h"
#include "instrucciones\InstrLET.h"
#include "instrucciones\InstrINPUT.h"
#include "instrucciones\InstrIF.h"

// Operandos
#include "operandos\OpCadena.h"
#include "operandos\OpEntero.h"
#include "operandos\OpFlotante.h"
#include "operandos\OpBooleano.h"

// Operadores
#include "operadores\OperadorDIVIDE.h"
#include "operadores\OperadorEQ.h"
#include "operadores\OperadorGT.h"
#include "operadores\OperadorGTE.h"
#include "operadores\OperadorLT.h"
#include "operadores\OperadorLTE.h"
#include "operadores\OperadorMULTI.h"
#include "operadores\OperadorNEQ.h"
#include "operadores\OperadorSUMA.h"
#include "operadores\OperadorRESTA.h"

using namespace std;

/// Clase que se ocupa del parseado del programa en BASIC proporcionado, generando una lista de instrucciones a ejecutar.
class Parser
{
    public:
        Parser(Input *i, Output *o);
        virtual ~Parser();
        /// Comprueba si una instrucción es válida
        /// @param inst Instrucción a ser validada.
        bool isValidInstr(const string inst);
        /// Ejecuta la lista de instrucciones generada.
        void ejecuta();
        /// Método que comprueba el estado de las variables después del parseado.
        /// @throw EMalformedBlockError
        void checkStatus() throw (EMalformedBlockError);
        /// Parsea una linea de programa, generando las instrucciones pertinentes e insertándolas en la lista de instrucciones a ejecutar.
        /// @param linea Línea a ser parseada.
        void parseaLinea(const string linea);
        /// Método que inicializa las variables de estado del parser (o las vacía en caso necesario)
        void inicializa();
        /// Obtiene la instrucción de la línea proporcionada
        /// @param linea Línea a ser parseada.
        /// @return La instrucción correspondiente, trimada.
        string getInstrucc(const string linea);
        /// Elimina la etiqueta de salto de la línea proporcionada
        /// @param linea Línea de la que se eliminará dicha etiqueta.
        string delLabel(const string linea);
        /// Declaración de clase amiga de la clase que representa una orden GOTO. Declarada de esta manera para
        /// permitir que dicha clase acceda a los atributos privados del parser. (puntero de ejecución)
        friend class InstrGOTO;
    private:
        Input *input;
        Output *output;
        /// variable a utilizar en la ejecución de la lista de instrucciones final. Será modificada por la clase @see InstrGOTO para emular los saltos.
        unsigned int ptrInstruccion;
        /// Mapa de etiquetas del programa a las que pueden apuntar los GOTO.
        map<string, int> etiquetas;
        /// Mapa de variables definidas en el programa.
        map<string,Operando *> variables;
        /// Instrucciones reconocidas por el programa.
        set<string> instrucciones;
        /// Palabras reservadas por el programa.
        set<string> rsvWords;
        /// Lista de instrucciones a ser ejecutadas.
        vector<Instruccion *> instRunnable;
#ifdef MIDEBUG
        /// Lista de instrucciones para debug
        vector<string> instDebug;
#endif
        /// Pila que representa los comienzos de bloques if y while. Se utiliza para comprobar su correcta anidación, así como término.
        stack<string> ifs;
        /// Función que procesa una linea, retornando si tiene o no etiqueta de salto
        /// @param[in,out] linea Línea a ser parseada. En caso de tener etiqueta, el parámetro se modifica, eliminado dicha etiqueta.
        /// @param[out] etiqueta Cadena donde se almacenará el nombre de la etiqueta.
        /// @return true En caso de que tenga etiqueta, además de poner dicha etiqueta en el parámetro del mismo nombre.
        bool linHasLabel(string &linea, string &etiqueta);
        /// función que devuelve la línea proporcionada sin la instrucción, es decir, sus argumentos
        /// @param linea Línea de la que se va a eliminar la instrucción
        /// @return la línea sin la instrucción
        string getArguments(const string linea);
        /// función que elimina la primera palabra de una línea. Se entiende por primera palabra, aquella que va desde el primer
        /// caracter hasta el primer espacio, o el fin de cadena en su caso.
        /// @param linea de la que se desea eliminar la primera palabra.
        /// @return la línea sin la primera palabra. Retorna cadena vacía en caso de que sólo hubiese una palabra en la línea original.
        string remFirstWord(const string linea);
        /// función que selecciona y devuelve la primera palabra de una línea. Se entiende por palabra lo mismo que en @see getArguments
        /// @param linea Línea de la que se desea seleccionar la primera palabra.
        /// @return La primera palabra de la línea proporcionada.
        string getFirstWord(const string linea);
        /// método que se ocupa de parsear la instrucción PRINT y generar las instrucciones pertinentes
        /// @param linea Línea con la instrucción mencionada
        void parsePRINT(const string linea);
        /// método que se ocupa de parsear la instrucción DIM y generar las instrucciones pertinentes
        /// @param linea Línea con la instrucción mencionada
        void parseDIM(const string linea);
        /// método que se ocupa de parsear la instrucción LET y generar las instrucciones pertinentes
        /// @param linea Línea con la instrucción mencionada
        void parseLET(const string linea);
        /// método que se ocupa de parsear la instrucción GOTO y generar las instrucciones pertinentes
        /// @param linea Línea con la instrucción mencionada
        void parseGOTO(const string linea);
        /// método que se ocupa de parsear la instrucción INPUT y generar las instrucciones pertinentes
        /// @param linea Línea con la instrucción mencionada
        void parseINPUT(const string linea);
        /// método que se ocupa de parsear la instrucción IF y generar las instrucciones pertinentes. El segundo parámetro se introduce
        /// con el objetivo de que este método sirva también para el parseado de la instrucción WHILE, cambiando dicho parámetro.
        /// @param linea Línea con la instrucción mencionada
        /// @param etiq Parámetro que representa la etiqueta con la que se almacenarán los datos necesarios en la pila @see ifs
        void parseIF(const string linea, const string etiq="lblIf");
        /// método que se ocupa de parsear la instrucción WHILE y generar las instrucciones pertinentes
        /// @param linea Línea con la instrucción mencionada
        void parseWHILE(const string linea);
        /// método que se ocupa de parsear la instrucción ELSE y generar las instrucciones pertinentes
        void parseELSE();
        /// método que se ocupa de parsear la instrucción ENDIF y generar las instrucciones pertinentes
        void parseENDIF();
        /// método que se ocupa de parsear la instrucción WEND y generar las instrucciones pertinentes
        void parseWEND();
        /// función que se ocupa de comprobar si una cadena tiene el formato de un nombre de variable
        /// @param linea Cadena de la que comprobar el formato.
        /// @return True si es un nombre de variable válido, false en caso contrario.
        bool isVarName(const string linea);
        /// función que se ocupa de comprobar si una cadena tiene el formato de un número (entero o flotante)
        /// @param linea Cadena de la que comprobar el formato.
        /// @return True si la cadena representa un número válido, false en caso contrario.
        bool isNumber(const string linea);
        /// función que se ocupa de comprobar si una cadena tiene el formato de un número flotante
        /// @param linea Cadena de la que comprobar el formato.
        /// @return True si la cadena representa un número flotante válido, false en caso contrario.
        bool isFlotante(const string linea);
        /// función que se ocupa de comprobar si una cadena tiene el formato de un número entero
        /// @param linea Cadena de la que comprobar el formato.
        /// @return True si la cadena representa un número entero válido, false en caso contrario.
        bool isEntero(const string linea);
        /// función que se ocupa de comprobar si una cadena tiene el formato de cadena aceptado por el programa.
        /// @param linea Cadena de la que comprobar el formato.
        /// @return True si la cadena representa una cadena válida, false en caso contrario.
        bool isCadena(const string linea);
        /// función que se ocupa de comprobar si una cadena tiene el formato de booleano aceptado por el programa.
        /// @param linea Cadena de la que comprobar el formato.
        /// @return True si la cadena representa un valor booleano válida, false en caso contrario.
        bool isBooleano(const string linea);
        /// función que se ocupa de determinar qué tipo de operando se le proporciona en el parámetro, crear el objeto
        /// adecuado y devolver una referencia a él.
        /// @param linea Cadena a partir de la que se pretende crear el objeto
        /// @return Puntero a un objeto cuya clase base es @see Operando.
        Operando* getOperando(const string linea);
        /// función que se ocupa de determinar qué tipo de operador se le proporciona en el parámetro, crear el objeto
        /// adecuado y devolver una referencia a él.
        /// @param linea Cadena a partir de la que se pretende crear el objeto
        /// @return Puntero a un objeto cuya clase base es @see Operador.
        Operador* getOperador(const string linea);
        /// función que devuelve la primera palabra de la línea proporcionada como parámetro, y modifica el parámetro, eliminando dicha palabra
        /// @param[in,out] linea Cadena a partir de la que se pretende crear el objeto
        /// @return Puntero a un objeto cuya clase base es @see Operando.
        string getVar(string &linea);
};

#endif // PARSER_H
