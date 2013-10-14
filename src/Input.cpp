#include "Input.h"
#include <QInputDialog>
#include <QString>
#include <stdexcept>

Input::Input()
{
    parentW = NULL;
}

Input::Input(QWidget *prnt){
    parentW = prnt;
}

std::string Input::ask(std::string texto){
    //string str;
    //std::cout << texto << std::endl;
    //getline( std::cin , str );
    //return str;

    //bool ok;
    //QString text = QInputDialog::getText(this, tr("Input"), tr(texto), QLineEdit::Normal, "", &ok, Qt::Dialog);
    QInputDialog dialog(parentW, Qt::Dialog);
    dialog.setInputMode(QInputDialog::TextInput);
    dialog.setLabelText(QString(texto.c_str()));
    dialog.setCancelButtonText("Cancelar");
    dialog.setOkButtonText("Aceptar");
    if(dialog.exec()){
        return dialog.textValue().toStdString();
    } else {
        throw std::runtime_error("Ejecución cancelada");
    }

}
