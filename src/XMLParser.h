#ifndef PROGRAMMING_C_XMLPARSER_H
#define PROGRAMMING_C_XMLPARSER_H


#include <string>

class XMLParser {
private:
    /**
     * @brief filename
     * Name of the file to parse.
     */
    std::string filename;
public:
    /**
     * @brief XMLParser
     * Constructor.
     * @param filename
     */
    explicit XMLParser(const std::string &filename);

    /**
     * @brief toString
     * @return
     */
    std::string toString();
};


#endif //PROGRAMMING_C_XMLPARSER_H
