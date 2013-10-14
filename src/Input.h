#ifndef INPUT_H
#define INPUT_H
#include <string>
#include <QWidget>

/// Clase que se ocupa de la entrada de datos del parser, transmitiéndosela al entorno gráfico
class Input
{
    public:
        Input();
        /// Constructor
        /// @param *prnt Puntero a un widget que será el padre de las ventanas que se necesite crear.
        Input(QWidget *prnt);
        /// Función que se ocupa de solicitar una entrada mostrando como descripción un texto
        /// @param texto Texto a mostrar en la pantalla de solicitud
        /// @return Cadena con la entrada del usuario
        std::string ask(std::string texto);
    private:
        /// Puntero a un widget que será el padre de las ventanas que se necesite crear.
        QWidget *parentW;
};

#endif // INPUT_H
