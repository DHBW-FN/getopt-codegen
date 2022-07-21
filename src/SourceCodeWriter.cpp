#include "SourceCodeWriter.h"
#include <boost/algorithm/string.hpp>

// Constructor
SourceCodeWriter::SourceCodeWriter(GetOptSetup *getOptSetup) {
    this->getOptSetup = getOptSetup;
}

// Getter
FILE *SourceCodeWriter::getHeaderFile() {
    if (headerFile == nullptr) {
        printf("Header file is nullptr\n");
        setHeaderFile(fopen(getGetOptSetup()->getHeaderFileName().c_str(), "w"));
    }
    return headerFile;
}

FILE *SourceCodeWriter::getSourceFile() {
    return sourceFile;
}

GetOptSetup *SourceCodeWriter::getGetOptSetup() const {
    return getOptSetup;
}

// Setter
void SourceCodeWriter::setHeaderFile(FILE *headerFile) {
    this->headerFile = headerFile;
}

void SourceCodeWriter::setSourceFile(FILE *sourceFile) {
    this->sourceFile = sourceFile;
}

/*
 * ALL HELPER FUNCTIONS HERE!!!
 */

void SourceCodeWriter::headerFileIncludes() {
    int subStringPosition = getOptSetup->getHeaderFileName().find('.');
    string defineString = getOptSetup->getHeaderFileName().substr(0, subStringPosition);
    boost::to_upper(defineString);
    fprintf(getHeaderFile(), "#ifndef %s_H\n#define %s_H\n\n#include <getopt.h>\n#include <iostream>\n"
                             "#include <string>\n\n", defineString.c_str(), defineString.c_str());

    //Here further generation-Methods

    fprintf(getHeaderFile(), "#endif //%s_H", defineString.c_str());
}

void SourceCodeWriter::sourceFileIncludes() {
    fprintf(getSourceFile(), "#include \"%s\"\n\n", getGetOptSetup()->getHeaderFileName().c_str());
}


void SourceCodeWriter::writeFile() {
    printf("Writing file...\n");

    headerFileIncludes();
    sourceFileIncludes();
}
