#include "CodeGenerator.h"
#include "XMLParser.h"
#include "SourceCodeWriter.h"
#include <iostream>

int main() {
    XMLParser parser("src3/exampleProgram.xml");
    std::cout << parser.toString() << std::endl;
    parser.parse();
    SourceCodeWriter writer = SourceCodeWriter(parser.getGetOptSetup());
    writer.writeFile();
    return 0;
}