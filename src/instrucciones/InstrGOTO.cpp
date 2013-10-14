#include "InstrGOTO.h"

InstrGOTO::InstrGOTO()
{
    //ctor
}

InstrGOTO::~InstrGOTO()
{
    //dtor
}

InstrGOTO::InstrGOTO(const string nEtiq, Parser* p)
{
    nombreEtiq = nEtiq;
    prsr = p;
}

bool InstrGOTO::ejecuta()
{
    if ( prsr->etiquetas.find( nombreEtiq ) == prsr->etiquetas.end() )
        throw EInvalidKeyword( nombreEtiq + " (no existe la etiqueta)" );
    prsr->ptrInstruccion = prsr->etiquetas[ nombreEtiq ] - 1;
    return true;
}

