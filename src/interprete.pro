#-------------------------------------------------
#
# Project created by QtCreator 2012-06-01T20:45:15
#
#-------------------------------------------------

QT       += core gui

TARGET = interprete
TEMPLATE = app


SOURCES += main.cpp\
    forms/mainwindow.cpp \
    utils.cpp \
    Scanner.cpp \
    Parser.cpp \
    Operando.cpp \
    Operador.cpp \
    Instruccion.cpp \
    excepciones/EMalformedBlockError.cpp \
    excepciones/EInvalidKeyword.cpp \
    excepciones/EFileNotFound.cpp \
    instrucciones/InstrPRINT.cpp \
    instrucciones/InstrLET.cpp \
    instrucciones/InstrINPUT.cpp \
    instrucciones/InstrIF.cpp \
    instrucciones/InstrGOTO.cpp \
    operadores/OperadorSUMA.cpp \
    operadores/OperadorRESTA.cpp \
    operadores/OperadorNEQ.cpp \
    operadores/OperadorMULTI.cpp \
    operadores/OperadorLTE.cpp \
    operadores/OperadorLT.cpp \
    operadores/OperadorGTE.cpp \
    operadores/OperadorGT.cpp \
    operadores/OperadorEQ.cpp \
    operadores/OperadorDIVIDE.cpp \
    operandos/OpFlotante.cpp \
    operandos/OpEntero.cpp \
    operandos/OpCadena.cpp \
    operandos/OpBooleano.cpp \
    Input.cpp \
    Output.cpp \
    excepciones/EExecAborted.cpp \
    forms/AboutBox.cpp

HEADERS  += forms/mainwindow.h \
    utils.h \
    Scanner.h \
    Parser.h \
    Operando.h \
    Operador.h \
    Instruccion.h \
    excepciones/EMalformedBlockError.h \
    excepciones/EInvalidKeyword.h \
    excepciones/EFileNotFound.h \
    instrucciones/InstrPRINT.h \
    instrucciones/InstrLET.h \
    instrucciones/InstrINPUT.h \
    instrucciones/InstrIF.h \
    instrucciones/InstrGOTO.h \
    operadores/OperadorSUMA.h \
    operadores/OperadorRESTA.h \
    operadores/OperadorNEQ.h \
    operadores/OperadorMULTI.h \
    operadores/OperadorLTE.h \
    operadores/OperadorLT.h \
    operadores/OperadorGTE.h \
    operadores/OperadorGT.h \
    operadores/OperadorEQ.h \
    operadores/OperadorDIVIDE.h \
    operandos/OpFlotante.h \
    operandos/OpEntero.h \
    operandos/OpCadena.h \
    operandos/OpBooleano.h \
    Input.h \
    Output.h \
    excepciones/EExecAborted.h \
    forms/AboutBox.h

FORMS    += forms/mainwindow.ui \
    forms/AboutBox.ui

CONFIG += static
static {
	CONFIG += static
	DEFINES += STATIC
	message("Static build.")
}
CONFIG += exceptions
