#include "InstrINPUT.h"

InstrINPUT::InstrINPUT()
{
    //ctor
}

InstrINPUT::InstrINPUT(Operando* txt, Operando* dest, Input *i)
{
    texto = txt;
    destino = dest;
    input = i;
}

InstrINPUT::~InstrINPUT()
{
    delete( destino );
    delete( texto );
}

bool InstrINPUT::ejecuta() throw (EInvalidConversion, EExecAborted)
{
    string str;
    try{
        str = input->ask(texto->getValue());
        destino->setValue( str );
    } catch (EInvalidConversion &e){
        throw;
    } catch (...){
        throw EExecAborted();
    }
    //cout << texto->getValue();
    //getline( std::cin , str );

    return true;
}
