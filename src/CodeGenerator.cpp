#include "CodeGenerator.h"
#include "XMLParser.h"
#include "HelpText.h"
#include <iostream>

int main() {
    XMLParser parser("example/Example.xml");
    std::cout << parser.toString() << std::endl;
    parser.parse();

    string printHelpText;

//    HelpText* help = nullptr;
//    help = new HelpText(parser.getGetOptSetup());
//
//    printHelpText = help->parseHelpMessage();
//
//    cout << printHelpText << endl;

//    FILE *file;
//
//    file = fopen("help.cpp", "a");
//    if (file == nullptr) {
//        perror("Error while creating file!");
//        return 1;
//    }
//
//    fprintf(file, "%s", printHelpText.c_str());
//
//    fclose(file);


    return 0;
}