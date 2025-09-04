#ifndef STRINGMANIPULATE_H_
#define STRINGMANIPULATE_H_

#include <iostream>
using std::string;
#include <list>
#include <string>

class StringManipulate {
    public:
        static std::list<string> trim(const string &str, const char &charToTrim){
            std::list<string> parts;
            int lastIndex = 0;
            for (int index = 0; index < str.length(); ++index){
                if (str[index] == charToTrim){
                    lastIndex = index;
                    string part = "";
                    for (int indexPart = lastIndex; indexPart < index; indexPart++){
                        part += str[indexPart];
                    }
                    parts.push_back(part);
                }
            }
            return parts;
        }
};

#endif