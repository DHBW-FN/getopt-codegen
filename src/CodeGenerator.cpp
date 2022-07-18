#include "CodeGenerator.h"
#include "XMLParser.h"
#include <iostream>

int main() {
    XMLParser parser("example/Example.xml");
    std::cout << parser.toString() << std::endl;
    parser.parse();

    return 0;
}