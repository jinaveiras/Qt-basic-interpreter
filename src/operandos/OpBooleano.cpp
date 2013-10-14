#include "OpBooleano.h"

const std::string OpBooleano::TIPO = "BOOLEANO";

OpBooleano::OpBooleano()
{
    valor = "";
    nombre = "";
}

OpBooleano::~OpBooleano()
{
    //dtor
}

OpBooleano::OpBooleano(std::string nom)
{
    valor = "";
    nombre = nom;
}

OpBooleano::OpBooleano(std::string nom, std::string val)
{
    valor = val;
    nombre = nom;
}

std::string OpBooleano::getValue()
{
    return valor;
}

std::string OpBooleano::getTipo()
{
    return TIPO;
}

std::string OpBooleano::getNombre()
{
    return nombre;
}

bool OpBooleano::isType(std::string val)
{
    return ( val == "TRUE" ) || ( val == "FALSE" );
}

std::string OpBooleano::boolToStr(bool x)
{
    string toret;
    if ( x )
        toret = "TRUE";
    else
        toret = "FALSE";
    return toret;
}

void OpBooleano::setValue(std::string val) throw (EInvalidConversion)
{
    if ( !isType( val ) )
        throw ( EInvalidConversion( val , TIPO ) );
    valor = val;
}

bool OpBooleano::getTypeValue()
{
     return ( valor == "TRUE" );
}
