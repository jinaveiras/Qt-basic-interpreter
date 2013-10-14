#include "Parser.h"

Parser::Parser(Input *i, Output *o)
{
    input  = i;
    output = o;
    string instrs[]= {"REM", "DIM", "LET", "PRINT", "INPUT", "GOTO", "IF", "WHILE", "ELSE", "ENDIF", "WEND"};
    instrucciones.insert(instrs,instrs+11);
    string reserv[]= {"REM", "DIM", "LET", "PRINT", "INPUT", "GOTO", "IF", "WHILE", "ELSE", "ENTERO",
                        "FLOTANTE", "BOOLEANO", "CADENA", "TRUE", "FALSE", "ENDIF", "WEND"};
    rsvWords.insert(reserv,reserv+17);
    ptrInstruccion = 0;
}

Parser::~Parser()
{
    for (map<string, Operando *>::iterator it = variables.begin(); it != variables.end(); ++it)
        delete( ( *it ).second );
    for (unsigned int i = 0; i < instRunnable.size(); ++i)
        delete( instRunnable[ i ] );
}

bool Parser::isValidInstr(const string inst)
{
    return ( instrucciones.find(inst) != instrucciones.end() );
}

void Parser::checkStatus() throw (EMalformedBlockError){
    if( !ifs.empty() ){
        output->escribe("Error de procesado.");
        throw EMalformedBlockError( "Error de anidamiento. Posible IF/WHILE sin ENDIF/WEND" );
    }
}

void Parser::inicializa(){
    for (map<string, Operando *>::iterator it = variables.begin(); it != variables.end(); ++it)
        delete( ( *it ).second );
    variables.clear();
    for (unsigned int i = 0; i < instRunnable.size(); ++i)
        delete( instRunnable[ i ] );
    instRunnable.clear();
    while (!ifs.empty())
        ifs.pop();
    ptrInstruccion = 0;
}

void Parser::ejecuta()
{
checkStatus();
#ifdef MIDEBUG
    string lbl = "";
    cout << "Instrucciones:" << endl;
    for (unsigned int i = 0; i < instDebug.size(); i++){
        cout << i << " \t";
        if ( instDebug[i].find("GOTO") != string::npos ){
            int pos = instDebug[i].find("GOTO") + 4 ;
            cout << instDebug[i].substr( 0 , pos ) << " ";
            cout << etiquetas[Utils::trim(instDebug[i].substr( pos, instDebug[i].size() ) )] << endl;
        } else {
            cout << instDebug[i] << endl;
        }
    }
    cout << endl << "Variables:" << endl;
    for (map<string, Operando *>::iterator it = variables.begin(); it != variables.end(); ++it)
        cout << (*it).first << (*it).second->getValue() << endl;
    cout << endl << "etiquetas:" << endl;
    for (map<string,int>::iterator it = etiquetas.begin(); it != etiquetas.end(); ++it)
        cout << (*it).first << ": instruccion " << (*it).second << endl;
#endif // MIDEBUG
    try{
        for (ptrInstruccion = 0; ptrInstruccion < instRunnable.size(); ++ptrInstruccion){
            instRunnable[ptrInstruccion]->ejecuta();
        }
    } catch (EExecAborted &e){
        throw;
    } catch (...){
        output->escribe("Error de ejecucion");
        throw;
    }
}

void Parser::parseaLinea(const string linea)
{
    string linTemp = linea;
    string instruccion;
    string etiqueta;
    bool tieneEtiq = linHasLabel(linTemp, etiqueta);
    instruccion = getInstrucc(linTemp);
    try{
        if (instruccion == "PRINT"){
            parsePRINT(linTemp);
        } else if (instruccion == "DIM"){
            parseDIM(linTemp);
        } else if (instruccion == "LET"){
            parseLET(linTemp);
        } else if (instruccion == "GOTO"){
            parseGOTO(linTemp);
        } else if (instruccion == "INPUT"){
            parseINPUT(linTemp);
        } else if (instruccion == "IF"){
            parseIF(linTemp);
        } else if (instruccion == "ELSE"){
            parseELSE();
        } else if (instruccion == "ENDIF"){
            parseENDIF();
        } else if (instruccion == "WHILE"){
            parseWHILE(linTemp);
        } else if (instruccion == "WEND"){
            parseWEND();
        }
        if (tieneEtiq) {
            etiquetas[etiqueta] = instRunnable.size() - 1;
        }
    } catch (exception &e){
        output->escribe("Error de procesado.");
        throw;
    }
}

void Parser::parseLET(const string linea)
{
    string linTemp = remFirstWord(linea); //elimino la instruccion (LET)
    if ( linTemp.empty() )
        throw EMalformedBlockError( linea + " (se esperaba variable)" );
    string nombre = getFirstWord(linTemp); //cojo el nombre de la variable
    if ( variables.find(nombre) == variables.end() )
        throw ( EInvalidKeyword( nombre + " (variable no definida)" ) );
    linTemp = remFirstWord(linTemp);
    if ( getFirstWord(linTemp) != "=" )
        throw EMalformedBlockError( linea );
    linTemp = remFirstWord(linTemp); //elimino el igual, queda la expresion
    Operando* oper1 = NULL;
    Operando* oper2 = NULL;
    Operador* operacion = NULL;
    try {
        oper1 = getOperando(getFirstWord(linTemp));
        linTemp = remFirstWord(linTemp);
        if ( (linTemp == "") && ( variables[nombre]->getTipo() != oper1->getTipo() ) ){
            throw EMalformedBlockError( "(los tipos no coinciden)" );
        }
        if ( linTemp.find_first_of("+-/*><=") != string::npos ) {

            if ( linTemp == "" )
                throw EMalformedBlockError(linea);

            operacion = getOperador(getFirstWord(linTemp));
            linTemp = remFirstWord(linTemp);

            if ( linTemp == "" )
                throw EMalformedBlockError(linea);

            oper2 = getOperando(getFirstWord(linTemp));

            linTemp = remFirstWord(linTemp);
            if ( linTemp != "" )
                throw EMalformedBlockError( linea + " (se esperaba fin de linea, se encontro: '" + linTemp + "' )" );
            if ( oper1->getTipo() != oper2->getTipo() ){
                throw EMalformedBlockError("(los tipos no coinciden)");
            }
            instRunnable.push_back(new InstrLET(variables[nombre],oper1,oper2,operacion));
        } else {
            instRunnable.push_back(new InstrLET(variables[nombre],oper1));
        }
#ifdef MIDEBUG
        instDebug.push_back(linea);
#endif // MIDEBUG
    }catch ( EMalformedBlockError &e ){
        if ( ( oper1 != NULL ) && ( variables.find( oper1->getNombre() ) == variables.end() ) )
            delete oper1;
        if ( ( oper2 != NULL ) && ( variables.find( oper2->getNombre() ) == variables.end() ) )
            delete oper2;
        if ( operacion != NULL )
            delete operacion;
        throw EMalformedBlockError( e.what() );
    }
    catch ( EInvalidKeyword &e ){
        if ( (oper1 != NULL ) && ( variables.find( oper1->getNombre() ) == variables.end() ) )
            delete oper1;
        if ( (oper2 != NULL ) && ( variables.find( oper2->getNombre() ) == variables.end() ) )
            delete oper2;
        if ( operacion != NULL )
            delete operacion;
        throw;
    }
}

void Parser::parseIF(const string linea, const string etiq)
{
    string linTemp = remFirstWord( linea ); //elimino la instruccion (IF)
    if ( linTemp.empty() )
        throw EMalformedBlockError( linea + " (se esperaba expresion)" );
    string etiqueta = etiq + OpEntero::intToStr( instRunnable.size() - 1 );
    ifs.push( etiqueta );
    Operando* oper1 = NULL;
    Operando* oper2 = NULL;
    Operador* operacion = NULL;
    try {
        oper1 = getOperando( getFirstWord( linTemp ) );

        if ( linTemp.find_first_of( "<>=" ) != string::npos ) {

            linTemp = remFirstWord( linTemp );
            if ( linTemp == "" )
                throw EMalformedBlockError( linea );

            operacion = getOperador( getFirstWord( linTemp ) );
            linTemp = remFirstWord( linTemp );

            if ( linTemp == "" )
                throw EMalformedBlockError(linea);

            oper2 = getOperando( getFirstWord(linTemp ) );

            linTemp = remFirstWord( linTemp );
            if ( linTemp != "" )
                throw EMalformedBlockError( linea );
            if ( oper1->getTipo() != oper2->getTipo() ){
                throw EMalformedBlockError( "(los tipos no coinciden)" );
            }
            instRunnable.push_back( new InstrIF(oper1, oper2, operacion, etiqueta, this) );
        } else {
            if ( oper1->getTipo() != "BOOLEANO" )
                throw EMalformedBlockError( oper1->getValue() + " (se esperaba booleano)" );
            instRunnable.push_back( new InstrIF(oper1, etiqueta, this) );
        }
#ifdef MIDEBUG
            instDebug.push_back( linea + " -> GOTO " + etiqueta );
#endif // MIDEBUG
    }catch ( EMalformedBlockError &e ){
        if ( ( oper1 != NULL ) && ( variables.find( oper1->getNombre() ) == variables.end() ) )
            delete oper1;
        if ( ( oper2 != NULL ) && ( variables.find( oper2->getNombre() ) == variables.end() ) )
            delete oper2;
        if ( operacion != NULL )
            delete operacion;
        throw EMalformedBlockError( linea );
    }
    catch ( EInvalidKeyword &e ){
        if ( ( oper1 != NULL ) && ( variables.find( oper1->getNombre() ) == variables.end() ) )
            delete oper1;
        if ( ( oper2 != NULL ) && ( variables.find( oper2->getNombre() ) == variables.end() ) )
            delete oper2;
        if ( operacion != NULL )
            delete operacion;
        throw;
    }
}

void Parser::parseWHILE( const string linea )
{
    string etiq = "lblWhileI" + OpEntero::intToStr( instRunnable.size() - 1 );
    ifs.push( etiq );
    etiquetas[etiq] = instRunnable.size();
    try{
        parseIF(linea, "lblWhile");

    } catch (exception &e){
        throw;
    }
}

void Parser::parseWEND(){
    if ( ifs.empty() )
        throw EMalformedBlockError( "se ha encontrado WEND sin WHILE" );

    string etiqueta = ifs.top();
    ifs.pop();
    etiquetas[etiqueta] = instRunnable.size() + 1;

    etiqueta = ifs.top();
    ifs.pop();

    instRunnable.push_back( new InstrGOTO( etiqueta, this ) );
#ifdef MIDEBUG
            instDebug.push_back( "GOTO " + etiqueta );
#endif // MIDEBUG
}

void Parser::parseINPUT(const string linea)
{
    string linTemp = remFirstWord( linea );
    Operando* texto = NULL;
    Operando* destino = NULL;
    try {
        string var = getVar( linTemp );
        if ( isCadena( var ) ){
            texto = new OpCadena( "" , Utils::trim( var , "\"" ) );
        } else if ( isVarName( var ) ){
            if ( variables.find(var) == variables.end() )
                throw EInvalidKeyword( linea + " (variable no definida)" );
            texto = variables[var];
        }
        var = getVar( linTemp );
        if ( isVarName( var ) ){
            if ( variables.find( var ) == variables.end() )
                throw EInvalidKeyword( linea + " (variable no definida)" );
            destino = variables[var];
        } else {
            throw EMalformedBlockError("INPUT (se esperaba variable)");
        }
        instRunnable.push_back( new InstrINPUT( texto, destino, input ) );
#ifdef MIDEBUG
            instDebug.push_back( linea );
#endif // MIDEBUG
    } catch (exception &e){
        delete texto;
        throw;
    }
}

void Parser::parsePRINT(const string linea)
{
    vector<Operando *> operandos;
    string linTemp = remFirstWord( linea );
    string var;
    if (linTemp.empty())
        operandos.push_back( new OpCadena( "" , "" ) );
    while ( !linTemp.empty() ){
        try{
            var = getVar( linTemp );
            if ( var.substr(0,1) == "\"" ){
                operandos.push_back( new OpCadena( "" , Utils::trim( var , "\"" ) ) );
            } else {
                if ( variables.find( var ) != variables.end() )
                    operandos.push_back( variables[var] );
                else
                    throw EInvalidKeyword( linea + " (variable no definida)" );
            }
        } catch (exception &e){
            throw;
        }
    }
    instRunnable.push_back( new InstrPRINT( operandos, output ) );
#ifdef MIDEBUG
    instDebug.push_back( linea );
#endif // MIDEBUG
}

void Parser::parseGOTO(const string linea)
{
    string linTemp = remFirstWord( linea );
    string var;
    try {
        var = getVar( linTemp );
        if ( ( !linTemp.empty() ) || ( !isVarName( var ) ) )
            throw EMalformedBlockError( linea + " (se esperaba etiqueta)" );
        instRunnable.push_back( new InstrGOTO( var , this ) );
#ifdef MIDEBUG
            instDebug.push_back( linea );
#endif // MIDEBUG
    } catch (exception &e){
        throw;
    }
}

void Parser::parseELSE()
{
    if ( ifs.empty() ){
        throw EMalformedBlockError( "se ha encontrado ELSE sin IF" );
    }
    string etiqueta = ifs.top();
    ifs.pop();
    if ( etiqueta.find("lblIf") == string::npos ){
        throw EMalformedBlockError( "se ha encontrado ELSE sin IF" );
    }
    string lblFinIf = "lblIf" + OpEntero::intToStr( instRunnable.size() - 1 );

    instRunnable.push_back( new InstrGOTO( lblFinIf , this ) );
#ifdef MIDEBUG
            instDebug.push_back( "GOTO " + lblFinIf );
#endif // MIDEBUG
    etiquetas[ etiqueta ] = instRunnable.size();

    ifs.push( lblFinIf );
}

void Parser::parseENDIF()
{
    if ( ifs.empty() )
        throw EMalformedBlockError( "se ha encontrado ENDIF sin IF/ELSE" );

    string etiqueta = ifs.top();
    ifs.pop();
    if ( etiqueta.find( "lblIf" ) == string::npos )
        throw EMalformedBlockError( "anidamiento incorrecto de bloque IF" );
    etiquetas[ etiqueta ] = instRunnable.size();
}

void Parser::parseDIM(const string linea)
{
    string linTemp = remFirstWord( linea );
    string nombre = getFirstWord( linTemp );
    if ( !isVarName( nombre ) )
        throw EInvalidKeyword( nombre + " (nombre de variable no valido)" );
    if ( rsvWords.find( nombre ) != rsvWords.end())
        throw EInvalidKeyword( linea + " -> " + nombre + " (palabra reservada)" );
    linTemp = remFirstWord( linTemp );
    if ( !(getFirstWord( linTemp ) == "as") ) {
        throw ( EMalformedBlockError( linea ) );
    }
    linTemp = remFirstWord( linTemp );
    if ( linTemp.find(" ") != string::npos )
        throw ( EMalformedBlockError( linea ) );
    if ( variables.find(nombre) == variables.end() ){
        if ( linTemp == "ENTERO" ){
            variables.insert( make_pair( nombre , new OpEntero( nombre ) ) );
        } else if ( linTemp == "CADENA" ){
            variables.insert( make_pair( nombre , new OpCadena( nombre ) ) );
        } else if ( linTemp == "BOOLEANO" ){
            variables.insert( make_pair( nombre , new OpBooleano( nombre ) ) );
        } else if ( linTemp == "FLOTANTE" ){
            variables.insert( make_pair( nombre , new OpFlotante( nombre ) ) );
        } else throw EInvalidKeyword( linTemp+" (Tipo de datos no soportado)" );
    }
}

string Parser::getVar(string &linea)
{
    string toret = getFirstWord( linea );
    linea = remFirstWord( linea );
    if ( !( ( linea == "" ) || ( ( linea.substr( 0 , 1 ) == "," ) && ( linea.size() > 1 ) ) ) ){
        if ( ( linea.substr( 0 , 1 ) != "," ) )
            throw( EMalformedBlockError( linea + " (se esperaba ,)" ) );
        else
            throw( EMalformedBlockError( linea + " (se esperaba operando)" ) );
    }
    linea = Utils::trim( Utils::trim( linea , "," ) );
    return toret;
}

string Parser::getArguments(const string linea)
{
    return remFirstWord( linea );
}

string Parser::getFirstWord(const string linea)
{
    string linTemp = Utils::trim( linea );
    string toret;
    if ( linTemp.substr( 0 , 1 ) == "\"" ){
        toret = linTemp.substr( 0 , linTemp.find( "\"" , 1 ) + 1 );
    }else {
        if ( linTemp.find_first_of( " ," ) != string::npos ){
            toret = linTemp.substr( 0 , linTemp.find_first_of( " ," ) );
        }else {
            toret = linTemp;
        }
    }
    return Utils::trim( toret );
}

string Parser::remFirstWord(const string linea)
{
    string toret;
    string linTemp = getFirstWord( linea );
    toret = linea.substr( linea.find( linTemp ) + linTemp.size() , linea.size() );
    return Utils::trim( toret );
}

string Parser::getInstrucc(string linea)
{
    return getFirstWord( linea );
}

string Parser::delLabel(const string linea)
{
    string toret = linea;
    if (linea.substr(0,1) == ":"){
       toret = remFirstWord(linea);
    }
    return toret;
}

bool Parser::linHasLabel(string &linea, string &etiqueta)
{
    bool toret = false;
    if ( linea.substr( 0 , 1 ) == ":" ){
        toret = true;
        etiqueta = Utils::trim( linea.substr ( 1 , linea.find(" ") ) );
        if ( !isVarName( etiqueta ) )
            throw EInvalidKeyword( etiqueta + " no es un identificador valido de etiqueta" );
        linea = remFirstWord( linea );
    }
    return toret;
}

bool Parser::isVarName(const string linea)
{
    bool toret;
    toret = ( ( linea[ 0 ] >= 'a' && linea[ 0 ] <= 'z')
             || ( linea[ 0 ] >= 'A' && linea[ 0 ] <= 'Z' ) )
            && ( rsvWords.find( linea ) == rsvWords.end() );
    for (unsigned int i = 1; toret && i < linea.size(); ++i){
        toret = ( linea[ i ] >= 'a' && linea[ i ] <= 'z')
                || ( linea[ i ] >= 'A' && linea[ i ] <= 'Z')
                || ( linea[ i ] >= '0' || linea[ i ] <= '9');
    }
    return toret;
}

bool Parser::isNumber(const string linea)
{
    bool toret;
    unsigned int decimales = 0;
    toret = ( linea[ 0 ] == '-' ) || ( ( linea[ 0 ] >= '0' ) && ( linea[ 0 ] <= '9' ) );
    for (unsigned int i = 1; toret && i < linea.size(); ++i){
        if ( linea[ i ] == '.')
            ++decimales;
        toret = ( ( linea[ i ] >= '0' ) && ( linea[ i ] <= '9' ) )
                || ( ( linea[ i ] == '.' ) && ( decimales < 2 ) );
    }
    return toret;
}

bool Parser::isFlotante(const string linea)
{
    return isNumber( linea ) && ( linea.find( "." ) != string::npos );
}

bool Parser::isEntero(const string linea)
{
    return isNumber( linea ) && ( linea.find( "." ) == string::npos );
}

bool Parser::isCadena(const string linea)
{
    return ( linea[ 0 ] == '"' ) && ( linea[ linea.size() - 1 ] == '"')
                && ( Utils::trim( linea , "\"" ).find( "\"" ) == string::npos );
}

bool Parser::isBooleano(const string linea)
{
    return OpBooleano::isType( linea );
}

Operando* Parser::getOperando(const string linea)
{
    Operando *toret;
    if ( linea.empty() )
        throw EMalformedBlockError( "(se esperaba operando)" );
    if ( isVarName( linea ) ){
        if ( variables.find( linea ) == variables.end() )
            throw ( EInvalidKeyword( linea + " (variable no definida)" ) );
        toret = variables[ linea ];
    } else {
        if ( isCadena( linea ) ) {
            toret = new OpCadena( "" , Utils::trim( linea , "\"" ) );
        } else if ( isBooleano( linea ) ){
            toret = new OpBooleano( "" , linea );
        } else if ( isEntero( linea ) ){
            toret = new OpEntero( "" , linea );
        } else if ( isFlotante( linea ) ){
            toret = new OpFlotante( "" , linea );
        } else throw ( EInvalidKeyword( linea + " no reconocido" ) );
    }
    return toret;
}

Operador* Parser::getOperador(const string linea)
{
    Operador* toret;
    if ( linea == "+" ){
        toret = new OperadorSUMA();
    } else if ( linea == "-" ){
        toret = new OperadorRESTA();
    } else if ( linea == "*" ){
        toret = new OperadorMULTI();
    } else if ( linea == "/" ){
        toret = new OperadorDIVIDE();
    } else if ( linea == "<" ){
        toret = new OperadorLT();
    } else if ( linea == ">" ){
        toret = new OperadorGT();
    } else if ( linea == "==" ){
        toret = new OperadorEQ();
    } else if ( linea == "<>" ){
        toret = new OperadorNEQ();
    } else if ( linea == ">=" ){
        toret = new OperadorGTE();
    } else if ( linea == "<=" ){
        toret = new OperadorLTE();
    } else throw ( EInvalidKeyword( linea + " operador no reconocido" ) );
    return toret;
}
