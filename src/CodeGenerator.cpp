/*
 * Editors: Tobias Goetz, Noel Kempter
 */

#include "CodeGenerator.h"
#include "XMLParser.h"
#include "SourceCodeWriter.h"
#include <getopt.h>

void CodeGenerator::setFilePath(const std::string &filename) {
    CodeGenerator::filePath = filename;
}

std::string CodeGenerator::getFilePath() {
    return CodeGenerator::filePath;
}

void CodeGenerator::run() {
    printf("Starting Codegenerator!\n");
    if(getFilePath().empty()){
        perror("The path to the XML-File must be set.");
        exit(EXIT_FAILURE);
    }

    XMLParser parser(getFilePath());
    parser.parse();
    SourceCodeWriter writer = SourceCodeWriter(parser.getGetOptSetup());
    writer.writeFile();
    printf("Codegenerator finished!\n");
}


int main(int argc, char **argv) {
    CodeGenerator generator;
    int c;
    int option_index;
    static struct option long_options[] = {
            {"path", required_argument, 0, 'p'},
            {0, 0, 0, 0}
    };

    while((c = getopt_long(argc, argv, "p:", long_options, &option_index)) != -1 ){
        switch(c){
            case 'p':
                if (optarg == nullptr){
                    perror("The path to the XML-File to be parsed was not set.");
                    exit(EXIT_FAILURE);
                }
                generator.setFilePath(optarg);
                break;
            case '?':
            default:
                perror("GetOpt encountered an unknown option.");
                exit(EXIT_FAILURE);
        }
    }
    if (optind < argc) {
        printf("non-option ARGV-elements: ");
        while (optind < argc)
            printf("%s ", argv[optind++]);
        printf("\n");
    }

    generator.run();
    return 0;
}
