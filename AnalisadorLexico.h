#ifndef ANALISADORLEXICO_H_
#define ANALISADORLEXICO_H_

#include <iostream>
using std::string;

class AnalisadorLexico{
    private:

    public:
        int static reconhecerComentarios(string line);
};

int AnalisadorLexico::reconhecerComentarios(string line){
    return line.find("//");
}

#endif