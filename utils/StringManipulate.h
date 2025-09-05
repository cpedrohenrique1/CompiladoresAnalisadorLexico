#ifndef STRINGMANIPULATE_H_
#define STRINGMANIPULATE_H_

#include <iostream>
using std::string;
#include <list>
#include <string>

class StringManipulate {
    public:
        static std::list<string> trim(const string &str, const char &charToTrim, const int& indexLine){
            std::list<string> parts;
            int lastIndex = 0;
            for (int index = 0; index < (int) str.length(); ++index){
                if (str[index] == charToTrim || index == (int) str.length() - 1){
                    string part = "[";
                    for (int indexPart = lastIndex; indexPart <= index; indexPart++){
                        part += str[indexPart];
                    }
                    part += ","+ std::to_string(indexLine) + "]";
                    parts.push_back(part);
                    lastIndex = index + 1;
                }
            }
            return parts;
        }
};

#endif