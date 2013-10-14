#include "Utils.h"

Utils::Utils()
{
    //ctor
}

string Utils::trim(string cad)
{
    return trim( cad, " \f\n\r\t\v" );
}

string Utils::trim(string cad, string caracteres)
{
    string tempLinea = cad;
    tempLinea.erase( 0, tempLinea.find_first_not_of( caracteres ) );
    tempLinea.erase( tempLinea.find_last_not_of( caracteres ) + 1 );
    return tempLinea;
}
