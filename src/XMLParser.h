#ifndef PROGRAMMING_C_XMLPARSER_H
#define PROGRAMMING_C_XMLPARSER_H


#include <string>

class XMLParser {
private:
    std::string filename;
public:
    std::string toString();

    explicit XMLParser(std::string filename);
};


#endif //PROGRAMMING_C_XMLPARSER_H
