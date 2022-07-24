/*
 * Editors: Tobias Goetz
 */
#include "XMLParser.h"
#include "SourceCodeWriter.h"
#include <iostream>
#include "Logger.h"

int main() {
    Logger::initFromConfig("logconfig.ini");
    LOG_INFO("Starting CodeGenerator");

    LOG_INFO("Starting XMLParser");
    XMLParser parser("example/Example.xml");
    parser.parse();
    LOG_INFO("Finished XMLParser");

    LOG_INFO("Starting SourceCodeWriter");
    SourceCodeWriter writer = SourceCodeWriter(parser.getGetOptSetup());
    writer.writeFile();
    LOG_INFO("Finished SourceCodeWriter");

    LOG_INFO("Codegenerator finished!");

    return 0;
}