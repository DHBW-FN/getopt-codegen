/*
 * Editors: Tobias Goetz
 */
#include "XMLParser.h"
#include "SourceCodeWriter.h"
#include <iostream>
#include "Logger.h"

int main() {
    Logger::initFromConfig("logconfig.ini");

    printf("Starting Codegenerator!\n");
    XMLParser parser("example/Example.xml");
    parser.parse();
    SourceCodeWriter writer = SourceCodeWriter(parser.getGetOptSetup());
    writer.writeFile();
    printf("Codegenerator finished!\n");
    LOG_DATA_FATAL("Codegenerator finished!");

    return 0;
}