#include "InstrPRINT.h"

InstrPRINT::InstrPRINT()
{
    //ctor
}

InstrPRINT::~InstrPRINT()
{
    for (unsigned int i = 0; i < op.size(); ++i)
        delete (op[ i ]);
}

InstrPRINT::InstrPRINT(vector<Operando *> txt, Output *o)
{
    op = txt;
    output = o;
}

bool InstrPRINT::ejecuta()
{
    unsigned int i;
    string tmpStr = "";
    for (i = 0; i < op.size(); i++){
        tmpStr += op[ i ]->getValue();
    }
    output->escribe(tmpStr);
    return true;
}
