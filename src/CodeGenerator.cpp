/*
 * Editors: Tobias Goetz
 */

#include "CodeGenerator.h"
#include "XMLParser.h"
#include "SourceCodeWriter.h"
#include <iostream>

int main() {
    printf("Starting Codegenerator!\n");
    XMLParser parser("example/example.xml");
    parser.parse();
    SourceCodeWriter writer = SourceCodeWriter(parser.getGetOptSetup());
    writer.writeFile();
    printf("Codegenerator finished!\n");
    return 0;
}