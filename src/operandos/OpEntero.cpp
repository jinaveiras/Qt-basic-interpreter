#include "OpEntero.h"

const std::string OpEntero::TIPO = "ENTERO";

OpEntero::OpEntero()
{
    valor = "";
    nombre = "";
}

OpEntero::OpEntero(std::string nom)
{
    valor = "";
    nombre = nom;
}

OpEntero::~OpEntero()
{
    //dtor
}

OpEntero::OpEntero(std::string nom, std::string val)
{
    valor = val;
    nombre = nom;
}

std::string OpEntero::getValue()
{
    return valor;
}

std::string OpEntero::getTipo()
{
    return OpEntero::TIPO;
}

std::string OpEntero::getNombre()
{
    return nombre;
}


void OpEntero::setValue(std::string val) throw (EInvalidConversion)
{
    if ( !isType( val ) )
        throw ( EInvalidConversion( val , TIPO ) );
    valor = val;
}

std::string OpEntero::intToStr(int x)
{
    ostringstream convert;
    convert << x;
    return convert.str();
}

bool OpEntero::isType(std::string val)
{
    int toret;
    return isT(&toret, val);
//    istringstream convert( val );
//    return ( ( convert >> toret ) && convert.eof() );
}

int OpEntero::getTypeValue()
{
    int toret;
    istringstream convert( valor );
    if ( !( ( convert >> toret ) && convert.eof() ) )
        throw ( EInvalidConversion( valor , TIPO ) );
    return toret;
}

