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
    createHeaderStructArgs();
    headerFileClass();

    //end of namespace
    if(!getGetOptSetup()->getNamespaceName().empty()){
        fprintf(getHeaderFile(), "}\n");
    }
}

void SourceCodeWriter::headerFileClass(){
    //start of class
    fprintf(getHeaderFile(), "class %s {\n", getGetOptSetup()->getClassName().c_str());

    fprintf(getHeaderFile(), "private:\n");
    //put all elements inside class -> private here
    fprintf(getHeaderFile(), "Args args;\n");

    fprintf(getHeaderFile(), "\n");
    fprintf(getHeaderFile(), "protected:\n");
    //put all elements inside class -> protected here

    fprintf(getHeaderFile(), "\n");
    fprintf(getHeaderFile(), "public:\n");
    //put all elements inside class -> public here

    //end of class
    fprintf(getHeaderFile(), "};\n");
}

void SourceCodeWriter::createHeaderStructArgs() {
    fprintf(getHeaderFile(), "struct Args {\n");
    for (auto &option : getGetOptSetup()->getOptions()) {
        fprintf(getHeaderFile(), "struct {\n");
        fprintf(getHeaderFile(), "bool isSet = false;\n");
        if (option.isHasArguments() != HasArguments::None) {
            fprintf(getHeaderFile(), "std::string value;\n");
        }
        fprintf(getHeaderFile(), "} %s;\n", determineArgsName(option).c_str());
    }
    fprintf(getHeaderFile(), "};\n\n");
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

std::string SourceCodeWriter::determineArgsName(const Option& option) {
    std::string argsName;
    if (!option.getInterface().empty()) {
        argsName = option.getInterface();
    } else if (!option.getLongOpt().empty()) {
        argsName = option.getLongOpt();
    } else if (!isblank(option.getShortOpt())) {
        argsName = option.getShortOpt();
    }

    argsName[0] = tolower(argsName[0], locale());

    // Removing all invalid characters from the name
    vector<char> invalidChars = {' ', '-', '.', ':'};
    for (auto &invalidChar: invalidChars) {
        while (argsName.find(invalidChar) != std::string::npos) {
            argsName[argsName.find(invalidChar) + 1] = toupper(argsName[argsName.find(invalidChar) + 1], locale());
            argsName.erase(argsName.find(invalidChar), 1);
        }
    }

    if (argsName.empty()) {
        perror("Every option must at least have either an Interface, a LongOpt or a ShortOpt.");
        exit(1);
    }

    return argsName;
}

void SourceCodeWriter::writeFile() {
    printf("Writing file...\n");

    //Write header files --> put methods here
    headerFileIncludes();

    //Write source files --> put methods here
    sourceFileIncludes();
    sourceFileNamespace();
}
