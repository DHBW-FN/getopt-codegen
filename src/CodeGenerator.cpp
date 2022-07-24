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

    initLogger();

    src::severity_logger< >& lg = my_logger::get();
    CUSTOM_LOG(lg, debug) << "Hello, world!";

//    src::severity_logger<logging::trivial::severity_level> lg;
//    CUSTOM_LOG(lg, debug) << "A regular message";

    return 0;
}