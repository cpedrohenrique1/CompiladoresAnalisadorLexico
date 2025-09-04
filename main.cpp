#include <iostream>
#include <fstream>
using namespace std;

#include "Arquivo.h"

int main()
{
    try
    {
        cout << "Escolha qual o arquivo a ser analisado: ";
        string nomeArquivo;
        cin >> nomeArquivo;
        Arquivo arquivo(nomeArquivo, new fstream());
        arquivo.lerArquivo();
    } catch(string e){
        cout << e << endl;
    }
    return 0;
}