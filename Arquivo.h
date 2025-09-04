#ifndef ARQUIVO_H_
#define ARQUIVO_H_

#include <iostream>
#include <fstream>
using std::ifstream;
using std::string;

#include "AnalisadorLexico.h"

class Arquivo
{
private:
    fstream *arquivo;
    AnalisadorLexico *analisadorLexico;
    void abrirArquivo(string nomeArquivo);
    void fecharArquivo();
    void escreverNoArquivo(string dados);

public:
    void lerArquivo();
    Arquivo(string nomeArquivo, fstream *arquivo);
    ~Arquivo();
};

Arquivo::Arquivo(string nomeArquivo, fstream *arquivo)
{
    if (!arquivo)
    {
        throw new string("Erro ao tentar abrir arquivo\n");
    }
    this->arquivo = arquivo;
    this->abrirArquivo(nomeArquivo);
    this->analisadorLexico = new AnalisadorLexico();
}

Arquivo::~Arquivo()
{
    this->fecharArquivo();
    delete this->arquivo;
    this->arquivo = NULL;
    delete this->analisadorLexico;
    this->analisadorLexico = NULL;
}

void Arquivo::abrirArquivo(string nomeArquivo)
{
    this->arquivo->open(nomeArquivo, std::ios::in);
    if (!this->arquivo->is_open())
    {
        throw new string("Erro ao tentar abrir arquivo\n");
    }
}

void Arquivo::lerArquivo()
{
    string fileContent;
    int lineNumber = 0;
    while (getline(*this->arquivo, fileContent))
    {
        lineNumber++;
        std::cout << fileContent << lineNumber << std::endl;
    }
    this->fecharArquivo();
}

void Arquivo::fecharArquivo()
{
    if (this->arquivo && this->arquivo->is_open())
    {
        this->arquivo->close();
    }
}

#endif