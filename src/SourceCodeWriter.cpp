#include "SourceCodeWriter.h"

// Constructor
SourceCodeWriter::SourceCodeWriter(GetOptSetup *getOptSetup) {
    this->getOptSetup = getOptSetup;
}

// Getter
FILE *SourceCodeWriter::getHeaderFile() {
    if (headerFile == nullptr) {
        printf("Header file is nullptr\n");
        if(getOptSetup->getHeaderFileName().empty() || getOptSetup->getSourceFileName().empty()){
            perror("Both the Header-Filename and the Source-Filename must be set.");
            exit(1);
        }
        setHeaderFile(fopen(getGetOptSetup()->getHeaderFileName().c_str(), "w"));
    }
    return headerFile;
}

FILE *SourceCodeWriter::getSourceFile() {
    if (sourceFile == nullptr) {
        printf("Source file is nullptr\n");
        if(getOptSetup->getHeaderFileName().empty() || getOptSetup->getSourceFileName().empty()){
            perror("Both the Header-Filename and the Source-Filename must be set.");
            exit(1);
        }
        setSourceFile(fopen(getGetOptSetup()->getSourceFileName().c_str(), "w"));
    }
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

void SourceCodeWriter::writeFile() {
    printf("Writing file...\n");
}
