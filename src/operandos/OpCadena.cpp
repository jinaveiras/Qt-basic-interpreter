#include "OpCadena.h"

const std::string OpCadena::TIPO = "CADENA";

OpCadena::OpCadena(){
    valor = "";
}

OpCadena::~OpCadena(){

}

OpCadena::OpCadena(std::string nom){
    valor = "";
    nombre = nom;
}

OpCadena::OpCadena(std::string nom, std::string val){
    valor = val;
    nombre = nom;
}

std::string OpCadena::getValue(){
    return valor;
}

std::string OpCadena::getTypeValue(){
    return getValue();
}

std::string OpCadena::getTipo(){
    return OpCadena::TIPO;
}

bool OpCadena::isType(std::string val){
    return true;
}

void OpCadena::setValue(std::string val){
    valor = val;
}

std::string OpCadena::getNombre(){
    return nombre;
}
