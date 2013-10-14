#include "InstrIF.h"

InstrIF::InstrIF()
{
    //ctor
}

InstrIF::~InstrIF()
{
    delete ( opA );
    delete ( opB );
    delete ( operacion );
    delete ( iGoto );
}

InstrIF::InstrIF(Operando* a, Operando* b, Operador* opr, std::string jmp, Parser* p)
{
    opA = a;
    opB = b;
    operacion = opr;
    iGoto = new InstrGOTO( jmp , p );
}

InstrIF::InstrIF(Operando* a, std::string jmp, Parser* p)
{
    opA = a;
    opB = NULL;
    operacion = NULL;
    iGoto = new InstrGOTO( jmp , p );
}

bool InstrIF::ejecuta()
{
    string toret;
    if ( operacion )
        toret = operacion->ejecuta( opA , opB );
    else
        if ( opA->getTipo() == "BOOLEANO" )
            toret = opA->getValue();
        else
            throw EInvalidInstr( "expresion no valida" );
    try {
        if ( toret == "FALSE" )
            iGoto->ejecuta();
    } catch (exception &e){
        throw;
    }
    return true;
}
