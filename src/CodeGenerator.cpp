/*
 * Editors: Tobias Goetz
 */

#include "CodeGenerator.h"
#include "XMLParser.h"
#include "SourceCodeWriter.h"
#include <iostream>

int main() {
    XMLParser parser("example/Example.xml");
    parser.parse();
    SourceCodeWriter writer = SourceCodeWriter(parser.getGetOptSetup());
    writer.writeFile();
    return 0;
}