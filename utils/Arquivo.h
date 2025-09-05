#ifndef ARQUIVO_H_
#define ARQUIVO_H_

#include <iostream>
#include <fstream>
using std::ifstream;
using std::string;

#include <list>
#include "StringManipulate.h"
#include "AnalisadorLexico.h"
#include <set>
class Arquivo
{
private:
    fstream *arquivo;
    string nomeArquivo;
    void abrirArquivo(string &nomeArquivo);
    void fecharArquivo();

public:
    void escreverArquivo(std::list<std::list<string>> &dados);
    std::list<std::list<string>> lerArquivo();
    Arquivo(string &nomeArquivo, fstream *arquivo);
    ~Arquivo();
};

Arquivo::Arquivo(string &nomeArquivo, fstream *arquivo)
{
    if (!arquivo)
    {
        throw string("Erro ao tentar abrir arquivo\n");
    }
    this->arquivo = arquivo;
    this->abrirArquivo(nomeArquivo);
    this->nomeArquivo = nomeArquivo;
}

Arquivo::~Arquivo()
{
    this->fecharArquivo();
    delete this->arquivo;
    this->arquivo = NULL;
}

void Arquivo::abrirArquivo(string &nomeArquivo)
{
    this->arquivo->open(nomeArquivo, std::ios::in);
    if (!this->arquivo->is_open())
    {
        throw string("Erro ao tentar abrir arquivo\n");
    }
}

std::list<std::list<string>> Arquivo::lerArquivo()
{
    string fileContent;
    std::list<std::list<string>> linhas;
    bool insideBlockComment = false;
    int indexLine = 0;

    while (getline(*this->arquivo, fileContent))
    {
        indexLine++;
        std::set<char> charSet(fileContent.begin(), fileContent.end());
        if (StringManipulate::whiteSpacesOnly(fileContent))
        {
            continue;
        }
        std::list<string> trimmedString;

        if (!insideBlockComment && AnalisadorLexico::openBlockComment(fileContent))
        {
            insideBlockComment = true;
            fileContent = fileContent.substr(0, AnalisadorLexico::reconhecerComentariosAbreBlocos(fileContent));
            trimmedString = StringManipulate::trim(fileContent, ' ', indexLine);
            linhas.push_back(trimmedString);
            continue;
        }
        if (insideBlockComment)
        {
            if (AnalisadorLexico::reconhecerComentariosFechaBlocos(fileContent) < fileContent.size())
            {
                insideBlockComment = false;
                fileContent = fileContent.substr(AnalisadorLexico::reconhecerComentariosFechaBlocos(fileContent), fileContent.size() - 1);
                trimmedString = StringManipulate::trim(fileContent, ' ', indexLine);
                linhas.push_back(trimmedString);
            }
            continue;
        }

        if (AnalisadorLexico::reconhecerComentariosSimples(fileContent) < fileContent.size())
        {
            fileContent = fileContent.substr(0, AnalisadorLexico::reconhecerComentariosSimples(fileContent));

            trimmedString = StringManipulate::trim(fileContent, ' ', indexLine);
            linhas.push_back(trimmedString);
            continue;
        }
        trimmedString = StringManipulate::trim(fileContent, ' ', indexLine);
        linhas.push_back(trimmedString);
    }

    this->fecharArquivo();
    return linhas;
}

void Arquivo::fecharArquivo()
{
    if (this->arquivo && this->arquivo->is_open())
    {
        this->arquivo->close();
    }
}

void Arquivo::escreverArquivo(std::list<std::list<string>> &dados)
{
    fstream arquivoEscrita;
    arquivoEscrita.open(this->nomeArquivo + ".o", std::ios::out);
    if (!arquivoEscrita.is_open())
    {
        throw string("Erro ao tentar abrir arquivo para escrita\n");
    }
    int indexLinha = 1;
    for (const std::list<string> linha : dados)
    {
        for (const string valor : linha)
        {
            arquivoEscrita << valor;
        }
        arquivoEscrita << std::endl;
        indexLinha++;
    }
}

#endif