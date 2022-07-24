/*
 * Editors: Tobias Goetz, Noel Kempter, Philipp Kuest, Niklas Holl
 */

#ifndef CODEGENERATOR_SOURCECODEWRITER_H
#define CODEGENERATOR_SOURCECODEWRITER_H

#include <iostream>
#include "models/GetOptSetup.h"

/**
 * @brief Class for the SourceCodeWriter
 */
class SourceCodeWriter {
private:
    /**
     * @brief The GetOptSetup
     */
    GetOptSetup *getOptSetup = nullptr;
    /**
     * @brief The header file
     */
    FILE *headerFile = nullptr;
    /**
     * @brief The source file
     */
    FILE *sourceFile = nullptr;

    // Helpers
    /**
     * @brief Get the type of the option depending on ConvertTo
     * @param option The option
     * @return The type of the option as string
     */
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

    /**
     * @brief
     * Generates the declaration of every virtual function in the Header-File
     */
    void createExternalFunctions();

    /**
     * @brief
     * Generates the declaration of the printVersion function in the Header-File
     */
    void createHeaderPrintVersion();

    /**
     * @brief
     * Generates the implementation of the printVersion function in the Source-File
     */
    void createSourcePrintVersion();

    /**
     * @brief
     * Generates the declaration of the printHelp function in the Header-File
     */
    void createHeaderPrintHelp();

    /**
     * @brief
     * Generates the implementation of the printHelp function in the Source-File
     */
    void createSourcePrintHelp();
public:
    // Constructor
    /**
     * @brief Constructor for the SourceCodeWriter
     * @param getOptSetup The GetOptSetup
     */
    explicit SourceCodeWriter(GetOptSetup *getOptSetup);
    /**
     * @brief Destructor for the SourceCodeWriter
     */
    ~SourceCodeWriter();

    /** @name Getter
    * @brief  Getter for the class
    */
    ///@{
    GetOptSetup *getGetOptSetup() const;
    FILE *getHeaderFile();
    FILE *getSourceFile();
    ///@}

    /** @name Getter
    * @brief  Getter for the class
    */
    ///@{
    void setHeaderFile(FILE *headerFile);
    void setSourceFile(FILE *sourceFile);
    ///@}

    // Methods
    /**
     * @brief Write the .h and .cpp files
     */
    void writeFile();
};


#endif //CODEGENERATOR_SOURCECODEWRITER_H
