/*
 * Editors: Tobias Goetz
 */
#include "XMLParser.h"
#include "SourceCodeWriter.h"
#include <iostream>
#include "Logger.h"

int main() {
    printf("Starting Codegenerator!\n");
    XMLParser parser("example/Example.xml");
    parser.parse();
    SourceCodeWriter writer = SourceCodeWriter(parser.getGetOptSetup());
    writer.writeFile();
    printf("Codegenerator finished!\n");

    Logger::initLogger();

    CUSTOM_LOG(Logger::lg, debug) << "A regular message";

    return 0;
}