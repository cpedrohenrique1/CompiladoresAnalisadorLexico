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

/**
    Classe responsavel por manipular arquivos de entrada e saída.
*/
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

/*
    Construtor da classe Arquivo.
    Recebe o nome do arquivo e um ponteiro para um objeto fstream.
    Abre o arquivo para leitura.
    Lança uma exceção se o arquivo não puder ser aberto.
*/
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

/*
    Destrutor da classe Arquivo.
    Fecha o arquivo se estiver aberto e libera a memória alocada para o objeto fstream.
*/
Arquivo::~Arquivo()
{
    this->fecharArquivo();
    delete this->arquivo;
    this->arquivo = NULL;
}
/*
    Método para abrir um arquivo.
    Recebe o nome do arquivo como parâmetro.
    Abre o arquivo para leitura.
    Lança uma exceção se o arquivo não puder ser aberto.
*/
void Arquivo::abrirArquivo(string &nomeArquivo)
{
    this->arquivo->open(nomeArquivo, std::ios::in);
    if (!this->arquivo->is_open())
    {
        throw string("Erro ao tentar abrir arquivo\n");
    }
}

/*
    Método para ler o conteúdo do arquivo.
    Retorna uma lista de listas de strings, onde cada lista interna representa uma linha do arquivo.
    Remove comentários e linhas em branco do arquivo.
    Lança uma exceção se ocorrer um erro durante a leitura do arquivo.
*/
std::list<std::list<string>> Arquivo::lerArquivo()
{
    string fileContent;
    std::list<std::list<string>> linhas;
    bool insideBlockComment = false;
    int indexLine = 0;

    while (getline(*this->arquivo, fileContent))
    {
        indexLine++;
        if (StringManipulate::whiteSpacesOnly(fileContent))
        {
            continue;
        }
        std::list<string> trimmedString;

        if (!insideBlockComment && AnalisadorLexico::openBlockComment(fileContent))
        {
            insideBlockComment = true;
            fileContent = fileContent.substr(0, AnalisadorLexico::reconhecerComentariosAbreBlocos(fileContent));
            if (fileContent.empty() || StringManipulate::whiteSpacesOnly(fileContent))
            {
                continue;
            }
            trimmedString = StringManipulate::trim(fileContent, ' ', indexLine);
            linhas.push_back(trimmedString);
            continue;
        }
        if (insideBlockComment)
        {
            if (AnalisadorLexico::reconhecerComentariosFechaBlocos(fileContent) < fileContent.size())
            {
                insideBlockComment = false;
                fileContent = fileContent.substr(AnalisadorLexico::reconhecerComentariosFechaBlocos(fileContent) + 2, fileContent.size());
                if (fileContent.empty() || StringManipulate::whiteSpacesOnly(fileContent))
                {
                    continue;
                }
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
        if (AnalisadorLexico::openCloseBlockComment(fileContent))
        {
            fileContent = fileContent.substr(0, AnalisadorLexico::reconhecerComentariosAbreBlocos(fileContent)) + fileContent.substr(AnalisadorLexico::reconhecerComentariosFechaBlocos(fileContent) + 2, fileContent.size());
            if (fileContent.empty() || StringManipulate::whiteSpacesOnly(fileContent))
            {
                continue;
            }
        }
        trimmedString = StringManipulate::trim(fileContent, ' ', indexLine);
        linhas.push_back(trimmedString);
    }

    this->fecharArquivo();
    return linhas;
}

/*
    Método para fechar o arquivo.
    Verifica se o arquivo está aberto e o fecha.
*/
void Arquivo::fecharArquivo()
{
    if (this->arquivo && this->arquivo->is_open())
    {
        this->arquivo->close();
    }
}

/*
    Método para escrever dados em um arquivo.
    Recebe uma lista de listas de strings, onde cada lista interna representa uma linha a ser escrita no arquivo.
    Escreve os dados no arquivo com a extensão ".o".
    Lança uma exceção se ocorrer um erro ao tentar abrir o arquivo para escrita.
*/
void Arquivo::escreverArquivo(std::list<std::list<string>> &dados)
{
    fstream arquivoEscrita;
    arquivoEscrita.open(this->nomeArquivo + ".o", std::ios::out);
    if (!arquivoEscrita.is_open())
    {
        throw string("Erro ao tentar abrir arquivo para escrita\n");
    }
    for (const std::list<string> linha : dados)
    {
        for (const string valor : linha)
        {
            arquivoEscrita << valor;
        }
        arquivoEscrita << std::endl;
    }
}

#endif