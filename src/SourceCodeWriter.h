#ifndef CODEGENERATOR_SOURCECODEWRITER_H
#define CODEGENERATOR_SOURCECODEWRITER_H

#include <iostream>
#include "models/GetOptSetup.h"

class SourceCodeWriter {
private:
    GetOptSetup *getOptSetup;
    FILE *headerFile = nullptr;
    FILE *sourceFile = nullptr;
public:
    // Constructor
    explicit SourceCodeWriter(GetOptSetup *getOptSetup);

    // Getter
    GetOptSetup *getGetOptSetup() const;
    FILE *getHeaderFile();
    FILE *getSourceFile();

    // Setter
    void setHeaderFile(FILE *headerFile);
    void setSourceFile(FILE *sourceFile);

    // Helpers
    void writeFile();
};


#endif //CODEGENERATOR_SOURCECODEWRITER_H
