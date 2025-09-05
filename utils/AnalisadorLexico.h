#ifndef ANALISADORLEXICO_H_
#define ANALISADORLEXICO_H_

#include <iostream>
using std::string;
#include "StringManipulate.h"

/**
    Classe responsavel por realizar a analise lexica do codigo fonte.
*/
class AnalisadorLexico
{
public:
    /*
        Métodos estáticos para reconhecer comentários em linhas de código.
        Cada método recebe uma string (linha de código) e retorna a posição do comentário ou um booleano indicando a presença de um comentário.
    */
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
    bool static openCloseBlockComment(string& line){
        return reconhecerComentariosAbreBlocos(line) < line.size() && reconhecerComentariosFechaBlocos(line) < line.size();
    }
};

#endif