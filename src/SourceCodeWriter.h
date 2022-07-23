/*
 * Editors: Tobias Goetz, Noel Kempter, Philipp Kuest
 */

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
    static string getValueTypeByOption(Option &option);

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

    /**
     * @brief
     * Generate Header-File declaration of the function that will handle Options-parsing
     */
    void createHeaderParsingFunction();

    /**
     * @brief
     * Generate implementation of the function that will handle Options-parsing
     */
    void createSourceParsingFunction();

    /**
     * @brief
     * Writes namespace into Source-File
     */
    void sourceFileNamespace();

    /**
     * @brief
     * Writes namespace into Header-File
     */
    void headerFileNamespace();

    /**
     * @brief
     * Writes Class into namespace in Header-File
     */
    void headerFileClass();

    /**
     * @brief
     * Writes exclusion check and execution of getOpts into Source-File
     */
    void sourceFileParse();

    /**
     * @brief
     * Determines the name the Args-Struct will have for any given Option
     * @param option
     * @return
     */
    static string determineArgsName(const Option& option);

    /**
     * @brief
     * Creates struct args for header
     */
    void createHeaderStructArgs();

    /**
     * @brief
     * Generates the declaration of the unknownOption-function
     */
    void createHeaderUnknownOption();

    /**
     * @brief
     * Generates the implementation of the unknownOption-function
     */
    void createSourceUnknownOption();

    /**
     * @brief
     * Generates the declaration of all Getters in the Header-File
     */
    void createHeaderGetter();

    /**
     * @brief
     * Generates the implementation of all Getters in the Header-File
     */
    void createSourceGetter();
};


#endif //CODEGENERATOR_SOURCECODEWRITER_H
