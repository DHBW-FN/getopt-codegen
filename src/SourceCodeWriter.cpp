#include "SourceCodeWriter.h"
#include <boost/algorithm/string.hpp>

// Constructor
SourceCodeWriter::SourceCodeWriter(GetOptSetup *getOptSetup) {
    if(getOptSetup->getSourceFileName().empty() || getOptSetup->getHeaderFileName().empty()){
        perror("Both the Header-Filename and the Sourcefilename must be set.");
        exit(1);
    }
    this->getOptSetup = getOptSetup;
}

SourceCodeWriter::~SourceCodeWriter() {
    printf("Destructor called.\n");
    if(this->headerFile != nullptr){
        fclose(this->headerFile);
    }
    if(this->sourceFile != nullptr){
        fclose(this->sourceFile);
    }
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
    if (sourceFile == nullptr) {
        printf("Source file is nullptr\n");
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

/**
 * @brief change type of arg to ConvertTo value
 * @param option a single option object
 * @return string to convert optarg respectively
 */
string SourceCodeWriter::convertParam(Option &option)
{
    // Check if ConvertTo option is STRING
    if (option.getConvertTo() != ConvertToOptions::STRING)
    {
        // If it's not STRING change return string depending on
        // value of ConvertTo
        if (option.getConvertTo() == ConvertToOptions::INTEGER)
        {
            return "boost::lexical_cast<int>(optarg)";
        }
        else if (option.getConvertTo() == ConvertToOptions::BOOLEAN)
        {
            return "boost::lexical_cast<bool>(optarg)";
        }
    }
    else
    {
        return "optarg";
    }
}

/**
 * @brief change type of value to ConvertTo value
 * @param option a single option object
 * @return string with correct value type
 */
string SourceCodeWriter::convertParamValue(Option &option)
{
    // Check if ConvertTo option is STRING
    if (option.getConvertTo() != ConvertToOptions::STRING)
    {
        // If it's not STRING change return string depending on
        // value of ConvertTo
        if (option.getConvertTo() == ConvertToOptions::INTEGER)
        {
            return "int value";
        }
        else if (option.getConvertTo() == ConvertToOptions::BOOLEAN)
        {
            return "bool value";
        }
    }
    else
    {
        return "std::string value";
    }
}


//from here on are all the headerFiles
void SourceCodeWriter::headerFileIncludes() {
    printf("Writing includes into header file\n");
    // Define static and always used includes here
    string includes[] = { "getopt.h", "iostream"};

    string defineString = getGetOptSetup()->getHeaderFileName()
            .substr(0, getGetOptSetup()->getHeaderFileName().find('.'));
    boost::to_upper(defineString);
    fprintf(getHeaderFile(), "#ifndef %s_H\n#define %s_H\n\n", defineString.c_str(), defineString.c_str());
    for (auto &include : includes) {
        fprintf(getHeaderFile(), "#include <%s>\n", include.c_str());
    }

    fprintf(getHeaderFile(), "\n");

    //Here further generation-Methods
    //struct method missing
    headerFileNamespace();

    // Close header file
    fprintf(getHeaderFile(), "\n#endif //%s_H", defineString.c_str());
}

void SourceCodeWriter::headerFileNamespace(){
    //start of namespace
    if(!getGetOptSetup()->getNamespaceName().empty()){
        fprintf(getHeaderFile(), "namespace %s {\n\n", getGetOptSetup()->getNamespaceName().c_str());
    }

    //put all elements inside namespace here
    headerFileClass();

    //end of namespace
    if(!getGetOptSetup()->getNamespaceName().empty()){
        fprintf(getHeaderFile(), "}\n");
    }
}

void SourceCodeWriter::headerFileClass(){
    //start of class
    fprintf(getHeaderFile(), "class %s {\n\n", getGetOptSetup()->getClassName().c_str());

    fprintf(getHeaderFile(), "private:\n\n");
    //put all elements inside class -> private here

    fprintf(getHeaderFile(), "protected:\n\n");
    //put all elements inside class -> protected here

    fprintf(getHeaderFile(), "public:\n\n");
    //put all elements inside class -> public here

    //end of class
    fprintf(getHeaderFile(), "};\n");
}

//from here on are all the sourceFiles
void SourceCodeWriter::sourceFileIncludes() {
    fprintf(getSourceFile(), "#include \"%s\"\n\n", getGetOptSetup()->getHeaderFileName().c_str());

    //Here further generation-Methods

    // Close source file includes
    fprintf(getSourceFile(), "\n");
}

void SourceCodeWriter::sourceFileNamespace(){
    //start of namespace
    if(!getGetOptSetup()->getNamespaceName().empty()){
        fprintf(getSourceFile(), "namespace %s {\n\n", getGetOptSetup()->getNamespaceName().c_str());
    }

    //put all elements inside namespace here

    //end of namespace
    if(!getGetOptSetup()->getNamespaceName().empty()){
        fprintf(getSourceFile(), "}\n");
    }
}

void SourceCodeWriter::writeFile() {
    printf("Writing file...\n");

    //Write header files --> put methods here
    headerFileIncludes();

    //Write source files --> put methods here
    sourceFileIncludes();
    sourceFileNamespace();
}
