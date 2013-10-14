#include "OperadorSUMA.h"

const std::string OperadorSUMA::SIMBOLO = "+";

OperadorSUMA::OperadorSUMA()
{
    //ctor
}

OperadorSUMA::~OperadorSUMA()
{
    //dtor
}

std::string OperadorSUMA::ejecuta(Operando* opA, Operando* opB)
{
    string toret;
    if ( opA->getTipo() != opB->getTipo() )
        throw ( EMalformedBlockError( "Los tipos no coinciden" ) );
    if ( opA->getTipo() == "BOOLEANO" )
        throw ( EInvalidInstr( "No se pueden sumar valores booleanos" ) );
    if ( opA->getTipo() == "ENTERO" ){
        int aux;
        OpEntero* a = dynamic_cast<OpEntero*>( opA );
        OpEntero* b = dynamic_cast<OpEntero*>( opB );
        aux = a->getTypeValue() + b->getTypeValue();
        toret = OpEntero::intToStr( aux );
    } else if ( opA->getTipo() == "FLOTANTE" ){
        float aux;
        OpFlotante* a = dynamic_cast<OpFlotante*>( opA );
        OpFlotante* b = dynamic_cast<OpFlotante*>( opB );
        aux = a->getTypeValue() + b->getTypeValue();
        toret = OpFlotante::floatToStr( aux );
    } else if ( opA->getTipo() == "CADENA"){
        toret = opA->getValue() + opB->getValue();
    }
    return toret;
}

std::string OperadorSUMA::getSimbolo()
{
    return OperadorSUMA::SIMBOLO;
}
