#include "CodeGenerator.h"
#include "XMLParser.h"
#include <iostream>

int main() {
    XMLParser parser("src/TestFile.txt");
    std::cout << parser.toString() << std::endl;
    return 0;
}