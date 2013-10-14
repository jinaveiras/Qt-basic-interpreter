#include "OperadorEQ.h"

const std::string OperadorEQ::SIMBOLO = "==";

OperadorEQ::OperadorEQ()
{
    //ctor
}

OperadorEQ::~OperadorEQ()
{
    //dtor
}

std::string OperadorEQ::ejecuta(Operando* opA, Operando* opB)
{
    string toret;
    if ( opA->getTipo() != opB->getTipo() )
        throw ( EMalformedBlockError( "Los tipos no coinciden" ) );
    if ( opA->getTipo() == "BOOLEANO" ){
        toret = OpBooleano::boolToStr( opA->getValue() == opB->getValue() );
    } else if ( opA->getTipo() == "ENTERO" ){
        OpEntero* a = dynamic_cast<OpEntero*>( opA );
        OpEntero* b = dynamic_cast<OpEntero*>( opB );
        toret = OpBooleano::boolToStr( a->getTypeValue() == b->getTypeValue() );
    } else if ( opA->getTipo() == "FLOTANTE" ){
        OpFlotante* a = dynamic_cast<OpFlotante*>( opA );
        OpFlotante* b = dynamic_cast<OpFlotante*>( opB );
        toret = OpBooleano::boolToStr( a->getTypeValue() == b->getTypeValue() );
    } else if ( opA->getTipo() == "CADENA" ){
        toret = OpBooleano::boolToStr( opA->getValue() == opB->getValue() );;
    }
    return toret;
}

std::string OperadorEQ::getSimbolo()
{
    return OperadorEQ::SIMBOLO;
}
