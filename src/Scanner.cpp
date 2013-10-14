#include "Scanner.h"

Scanner::Scanner(string ruta, Input *i, Output *o)
{
    this->rutaProg = ruta;
    prog = NULL;
    inicializa(i,o);
}

Scanner::Scanner(QPlainTextEdit *t, Input *i, Output *o){
    prog = t;
    inicializa(i,o);
}

void Scanner::inicializa(Input *i, Output *o){
    input = i;
    output = o;
    p = new Parser(input, output);
}

Scanner::~Scanner()
{
    delete prog;
    delete p;
}

bool Scanner::scan() throw (EFileNotFound, EInvalidKeyword)
{
//    ifstream fichero( rutaProg.c_str() );

//    if( !fichero ) {
//        throw EFileNotFound(rutaProg);
//    }
    string linea;
    string strTmp;

    p->inicializa();
    output->limpiar();
    output->escribe("Parseando...");

    try {
        for (int i = 0; i < prog->document()->blockCount(); ++i){
            QTextBlock lin = prog->document()->findBlockByNumber(i);
            linea = Utils::trim(lin.text().toStdString());
            strTmp = "Procesando linea: ";
            strTmp += linea;
            output->escribe(strTmp);
            this->procLinea(linea);
        }


        //while ( !fichero.eof() ){
            //getline(fichero, linea);
            //this->procLinea(Utils::trim(linea));
        //}
        //p->ejecuta();
        p->checkStatus();
        output->escribe("¡Parseado correcto!");
    }
    catch (EMalformedBlockError &e){
        string tmpStr = "Sintaxis no reconocida en el bloque: ";
        tmpStr += e.what();
        output->escribe(tmpStr);
        return false;
        //cout << "Sintaxis no reconocida en el bloque: " << e.what() << endl;
    }
    catch (exception &e){
        output->escribe(e.what());
        return false;
        //cout << e.what() << endl;
    }

    return true;
    //fichero.close();

}

void Scanner::ejecuta(){

    try{
        if (scan()){
            output->limpiar();
            output->escribe("Ejecutando...");
            p->ejecuta();
            output->escribe("Ejecución terminada correctamente.");
        }
    }
    catch (EMalformedBlockError &e){
        string tmpStr = "Sintaxis no reconocida en el bloque: ";
        tmpStr += e.what();
        output->escribe(tmpStr);
    }
    catch (EExecAborted &e){
        output->escribe(e.what());
    }
    catch (exception &e){
        output->escribe(e.what());
    }
    catch (...){
        output->escribe("Error desconocido");
    }

}

void Scanner::procLinea(string lin)
{
    string instruccion;

    instruccion = p->getInstrucc(p->delLabel(lin));
    if (!p->isValidInstr(instruccion)) {
        throw EInvalidInstr(instruccion);
    }
    try{
        p->parseaLinea(lin);
    } catch (exception &e){
        throw;
    }
}
