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
    fprintf(getHeaderFile(), "namespace %s {\n\n", getGetOptSetup()->getNamespaceName().c_str());

    //put all elements inside namespace here
    headerFileClass();

    //end of namespace
    fprintf(getHeaderFile(), "}\n");
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
    fprintf(getHeaderFile(), "}\n");
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
    fprintf(getSourceFile(), "namespace %s {\n\n", getGetOptSetup()->getNamespaceName().c_str());

    //put all elements inside namespace here

    //end of namespace
    fprintf(getSourceFile(), "}\n");
}

void SourceCodeWriter::writeFile() {
    printf("Writing file...\n");

    //Write header files --> put methods here
    headerFileIncludes();

    //Write source files --> put methods here
    sourceFileIncludes();
    sourceFileNamespace();
}
