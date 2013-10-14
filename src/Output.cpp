#include "Output.h"

Output::Output(QPlainTextEdit *s)
{
    salida = s;
}

void Output::escribe(std::string texto)
{
    salida->appendPlainText(QString(texto.c_str()));
}

void Output::escribeLn(std::string texto)
{
    std::string tmpStr = texto;
    tmpStr = texto+"\r\n";
    salida->appendPlainText(QString(tmpStr.c_str()));
}

void Output::limpiar(){
    salida->clear();
}
