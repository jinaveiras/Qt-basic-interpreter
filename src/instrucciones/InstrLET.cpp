#include "InstrLET.h"

InstrLET::InstrLET()
{
    destino = opA = opB = NULL;
    operador = NULL;
}

InstrLET::~InstrLET()
{
    delete( destino );
    delete( opA );
    delete( opB );
    delete( operador );
}

InstrLET::InstrLET(Operando* dest, Operando* a)
{
    destino = dest;
    opA = a;
    opB = NULL;
    operador = NULL;
}

InstrLET::InstrLET(Operando* dest, Operando* a, Operando* b, Operador* op)
{
    destino = dest;
    opA = a;
    opB = b;
    operador = op;
}

bool InstrLET::ejecuta()
{
    if ( ( opB == NULL ) || ( operador == NULL ) )
        destino->setValue( opA->getValue() );
    else
        destino->setValue( operador->ejecuta( opA , opB ) );
    return true;
}
