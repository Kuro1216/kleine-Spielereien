#include "headerfile.hpp"
#include <string>
#include <fstream>
#include <iostream>
using namespace std;


string DigraphExeption::getInvolved(void){
    return _involved;
}

string DigraphExeption::getError(void){
    return _error;
}

string DigraphExeption::getHint(void){
    return _hint;
}

int DigraphExeption::getCode(void){
    return _code;
}

void DigraphExeption::setInvolved(string involved){
    _involved = involved;
}

void DigraphExeption::setError(string error){
    _error = error;
}

void DigraphExeption::setHint(string hint){
    _hint = hint;
}

void DigraphExeption::setCode(int code){
    _code = code;
}

DigraphExeption::DigraphExeption(void){
    _error = "";
    _involved = "";
    _hint = "";
    _code = 0;
}

DigraphExeption::~DigraphExeption(void){
}
