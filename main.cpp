#include <iostream>
#include <fstream>
using namespace std;

#include "Arquivo.h"

int main(){
    cout << "Escolha qual o arquivo a ser analisado: ";
    string nomeArquivo;
    cin >> nomeArquivo;
    Arquivo arquivo(new ifstream(nomeArquivo));
    arquivo.lerArquivo();
    return 0;
}