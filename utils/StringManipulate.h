#ifndef STRINGMANIPULATE_H_
#define STRINGMANIPULATE_H_

#include <iostream>
using std::string;
#include <list>
#include <string>
#include <set>
/**
    Classe para manipulação de strings e verificação de espaços em branco
*/
class StringManipulate {
    public:
        /*
          Função para remover determinado caracter de uma string
         */
        static std::list<string> trim(const string &str, const char &charToTrim, const int& indexLine){
            std::list<string> parts;
            int lastIndex = 0;
            for (int index = 0; index < (int) str.length(); ++index){
                if (str[index] == charToTrim || index == (int) str.length() - 1){
                    string part = "[";
                    for (int indexPart = lastIndex; indexPart < index; indexPart++){
                        part += str[indexPart];
                    }
                    if (index == (int) str.length() - 1 && str[index] != ' '){
                        part += str[index];
                    }
                    part += ","+ std::to_string(indexLine) + "]";
                    parts.push_back(part);
                    lastIndex = index + 1;
                }
            }
            return parts;
        }
        // Função para verificar se uma string é composta apenas por espaços em branco
        static bool whiteSpacesOnly(const string& line){
            if (line.empty()){
                return true;
            }
            std::set<char> setString(line.begin(), line.end());
            if (((setString.size() == 1) && (*setString.begin() == ' ')))
                return true;
            return false;
        }
};

#endif