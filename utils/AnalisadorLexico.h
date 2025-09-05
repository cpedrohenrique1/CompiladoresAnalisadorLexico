#ifndef ANALISADORLEXICO_H_
#define ANALISADORLEXICO_H_

#include <iostream>
using std::string;
#include "StringManipulate.h"

class AnalisadorLexico
{
public:
    int static reconhecerComentariosSimples(string &line)
    {
        return line.find("//");
    }
    int static reconhecerComentariosAbreBlocos(string &line)
    {
        return line.find("/*");
    }
    int static reconhecerComentariosFechaBlocos(string& line){
        return line.find("*/");
    }
    bool static openBlockComment(string& line){
        return reconhecerComentariosAbreBlocos(line) < line.size() && !(reconhecerComentariosFechaBlocos(line) < line.size());
    }
};

#endif