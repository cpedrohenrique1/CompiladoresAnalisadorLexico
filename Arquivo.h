#ifndef ARQUIVO_H_
#define ARQUIVO_H_

#include <iostream>
#include <fstream>
using std::string;
using std::ifstream;

#include "AnalisadorLexico.h"

class Arquivo{
    private:
        ifstream* arquivo;
        AnalisadorLexico* analisadorLexico;
    public:
        Arquivo(ifstream* arquivo);
        ~Arquivo();
        void lerArquivo();
        void fecharArquivo();
        void escreverNoArquivo(string dados);
};

Arquivo::Arquivo(ifstream* arquivo){
    if (!arquivo){
        throw new string("Erro ao tentar abrir arquivo\n");
    }
    this->arquivo = arquivo;
    this->analisadorLexico = new AnalisadorLexico();
}

Arquivo::~Arquivo(){
    this->arquivo->close();
    delete this->arquivo;
    this->arquivo = NULL;
    delete this->analisadorLexico;
    this->analisadorLexico = NULL;
}

void Arquivo::lerArquivo(){
    string fileContent;
    while (*arquivo >> fileContent) {
        std::cout << this->analisadorLexico->reconhecerComentarios(fileContent);
        std::cout<< fileContent << '\n';
    }
}

#endif