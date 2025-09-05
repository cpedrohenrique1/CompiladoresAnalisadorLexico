#include <iostream>
#include <fstream>
using namespace std;

#include "utils/Arquivo.h"
/* para iniciar o programa pode ser passado o nome do arquivo como argumento
    ou se nenhum argumento for passado, o programa pedirá o nome do arquivo
    a ser analisado
    Exemplo de uso:
    ./programa arquivo.txt
    ou
    ./programa
    Escolha qual o arquivo a ser analisado: arquivo.txt
*/ 
int main(int argc, char* argv[])
{
    try
    {
        string nomeArquivo;
        if (argc != 2){
            cout << "Escolha qual o arquivo a ser analisado: ";
            cin >> nomeArquivo;
        } else {
            nomeArquivo = argv[1];
        }
        Arquivo arquivo(nomeArquivo, new fstream());
        std::list<std::list<string>> linhas = arquivo.lerArquivo();
        arquivo.escreverArquivo(linhas);
    } catch(string e){
        cout << e << endl;
    }
    return 0;
}