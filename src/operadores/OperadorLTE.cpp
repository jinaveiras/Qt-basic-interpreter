#include "OperadorLTE.h"

const std::string OperadorLTE::SIMBOLO = ">";

OperadorLTE::OperadorLTE()
{
    //ctor
}

OperadorLTE::~OperadorLTE()
{
    //dtor
}

std::string OperadorLTE::ejecuta(Operando* opA, Operando* opB)
{
    string toret;
    if ( opA->getTipo() != opB->getTipo() )
        throw (EMalformedBlockError( "Los tipos no coinciden" ) );
    if ( opA->getTipo() == "BOOLEANO" ){
        OpBooleano* a = dynamic_cast<OpBooleano*>( opA );
        OpBooleano* b = dynamic_cast<OpBooleano*>( opB );
        toret = OpBooleano::boolToStr( a->getTypeValue() <= b->getTypeValue() );
    } else if (opA->getTipo() == "ENTERO"){
        OpEntero* a = dynamic_cast<OpEntero*>( opA );
        OpEntero* b = dynamic_cast<OpEntero*>( opB );
        toret = OpBooleano::boolToStr( a->getTypeValue() <= b->getTypeValue() );
    } else if ( opA->getTipo() == "FLOTANTE" ){
        OpFlotante* a = dynamic_cast<OpFlotante*>( opA );
        OpFlotante* b = dynamic_cast<OpFlotante*>( opB );
        toret = OpBooleano::boolToStr(a->getTypeValue() <= b->getTypeValue() );
    } else if ( opA->getTipo() == "CADENA" ){
        toret = OpBooleano::boolToStr( opA->getValue() <= opB->getValue() );
    }
    return toret;
}

std::string OperadorLTE::getSimbolo()
{
    return OperadorLTE::SIMBOLO;
}
