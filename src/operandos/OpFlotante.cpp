#include "OpFlotante.h"

const std::string OpFlotante::TIPO = "FLOTANTE";

OpFlotante::OpFlotante()
{
    valor = "";
    nombre = "";
}

OpFlotante::OpFlotante(std::string nom)
{
    valor = "";
    nombre = nom;
}

OpFlotante::OpFlotante(std::string nom, std::string val)
{
    valor = val;
    nombre = nom;
}

std::string OpFlotante::getValue()
{
    return valor;
}

std::string OpFlotante::getTipo()
{
    return OpFlotante::TIPO;
}

void OpFlotante::setValue(std::string val) throw (EInvalidConversion)
{
    if ( !isType( val ) )
        throw ( EInvalidConversion( val , TIPO ) );
    valor = val;
}

std::string OpFlotante::getNombre()
{
    return nombre;
}

bool OpFlotante::isType(std::string val)
{
    float toret;
    istringstream convert( val );
    return ( ( convert >> toret ) && convert.eof() );
}

float OpFlotante::getTypeValue()
{
    float toret;
    istringstream convert( valor );
    if ( !( ( convert >> toret) && convert.eof() ) )
        throw ( EInvalidConversion( valor , TIPO ) );
    return toret;
}

std::string OpFlotante::floatToStr(float x){
    ostringstream convert;
    convert << x;
    return convert.str();
}

OpFlotante::~OpFlotante(){
}
