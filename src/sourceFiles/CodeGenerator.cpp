/*
 * Editors: Tobias Goetz
 */

#include "headerFiles/CodeGenerator.h"
#include "headerFiles/XMLParser.h"
#include "headerFiles/SourceCodeWriter.h"
#include <iostream>

int main() {
    printf("Starting Codegenerator!\n");
    XMLParser parser("example/Example.xml");
    parser.parse();
    SourceCodeWriter writer = SourceCodeWriter(parser.getGetOptSetup());
    writer.writeFile();
    printf("Codegenerator finished!\n");
    return 0;
}