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
    ~SourceCodeWriter();

    // Getter
    GetOptSetup *getGetOptSetup() const;
    FILE *getHeaderFile();
    FILE *getSourceFile();

    // Setter
    void setHeaderFile(FILE *headerFile);
    void setSourceFile(FILE *sourceFile);

    // Helpers
    void writeFile();

    // Write code functions

    /**
     * @brief
     * Writes definitions and includes into Header-File
     */
    void headerFileIncludes();

    /**
     * @brief
     * Writes includes into Source-File
     */
    void sourceFileIncludes();
};


#endif //CODEGENERATOR_SOURCECODEWRITER_H
