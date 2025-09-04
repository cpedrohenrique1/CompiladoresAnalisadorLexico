#include <iostream>
#include <fstream>
using namespace std;

#include "utils/Arquivo.h"

int main(int argc, char* argv[])
{
    try
    {
        string nomeArquivo;
        if (argc == 1){
            cout << "Escolha qual o arquivo a ser analisado: ";
            cin >> nomeArquivo;
        } else {
            nomeArquivo = argv[1];
        }
        Arquivo arquivo(nomeArquivo, new fstream());
        arquivo.lerArquivo();
    } catch(string e){
        cout << e << endl;
    }
    return 0;
}