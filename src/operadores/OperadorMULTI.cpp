#include "OperadorMULTI.h"

const std::string OperadorMULTI::SIMBOLO = "*";

OperadorMULTI::OperadorMULTI()
{
    //ctor
}

OperadorMULTI::~OperadorMULTI()
{
    //dtor
}

std::string OperadorMULTI::ejecuta(Operando* opA, Operando* opB)
{
    string toret;
    if ( opA->getTipo() != opB->getTipo() )
        throw ( EMalformedBlockError( "Los tipos no coinciden" ) );
    if ( opA->getTipo() == "BOOLEANO" )
        throw ( EInvalidInstr( "No se pueden multiplicar valores booleanos" ) );
    if ( opA->getTipo() == "ENTERO" ){
        int aux;
        OpEntero* a = dynamic_cast<OpEntero*>( opA );
        OpEntero* b = dynamic_cast<OpEntero*>( opB );
        aux = a->getTypeValue() * b->getTypeValue();
        toret = OpEntero::intToStr( aux );
    } else if ( opA->getTipo() == "FLOTANTE" ){
        float aux;
        OpFlotante* a = dynamic_cast<OpFlotante*>( opA );
        OpFlotante* b = dynamic_cast<OpFlotante*>( opB );
        aux = a->getTypeValue() * b->getTypeValue();
        toret = OpFlotante::floatToStr( aux );
    } else if ( opA->getTipo() == "CADENA" ){
        throw (EInvalidInstr("No se pueden multiplicar valores de cadena"));
    }
    return toret;
}

std::string OperadorMULTI::getSimbolo()
{
    return OperadorMULTI::SIMBOLO;
}
