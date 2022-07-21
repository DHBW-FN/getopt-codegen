#include "SourceCodeWriter.h"
#include <boost/algorithm/string.hpp>

// Constructor
SourceCodeWriter::SourceCodeWriter(GetOptSetup *getOptSetup) {
    if (getOptSetup->getSourceFileName().empty() || getOptSetup->getHeaderFileName().empty()) {
        perror("Both the Header-Filename and the Sourcefilename must be set.");
        exit(1);
    }
    this->getOptSetup = getOptSetup;
}

SourceCodeWriter::~SourceCodeWriter() {
    printf("Destructor called.\n");
    if (this->headerFile != nullptr) {
        fclose(this->headerFile);
    }
    if (this->sourceFile != nullptr) {
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
    string includes[] = {"getopt.h", "iostream"};

    string defineString = getGetOptSetup()->getHeaderFileName()
            .substr(0, getGetOptSetup()->getHeaderFileName().find('.'));
    boost::to_upper(defineString);
    fprintf(getHeaderFile(), "#ifndef %s_H\n#define %s_H\n\n", defineString.c_str(), defineString.c_str());
    for (auto &include: includes) {
        fprintf(getHeaderFile(), "#include <%s>\n", include.c_str());
    }

    fprintf(getHeaderFile(), "\n");

    //Here further generation-Methods
    //struct method missing
    headerFileNamespace();
    createHeaderParsingFunction();

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
    createHeaderParsingFunction();
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
    if(!getGetOptSetup()->getNamespaceName().empty()){
        fprintf(getSourceFile(), "namespace %s {\n\n", getGetOptSetup()->getNamespaceName().c_str());
    }

    createSourceParsingFunction();
    //put all elements inside namespace here

    //end of namespace
    if(!getGetOptSetup()->getNamespaceName().empty()){
        fprintf(getSourceFile(), "}\n");
    }
}

void SourceCodeWriter::createHeaderParsingFunction() {
    fprintf(getHeaderFile(), "void parseOptions(int argc, char **argv);");
}

void SourceCodeWriter::createSourceParsingFunction() {
    vector<Option> options = getGetOptSetup()->getOptions();
    fprintf(getSourceFile(), "void %s::parseOptions(int argc, char **argv){\n"
                             "checkExclusions(argc, argv);\n opterr = 0;"
                             "int opt;\nstatic struct option long_options[] = {\n",
                             getGetOptSetup()->getClassName().c_str());

    int longOptsWithoutShortOpt = 0;

    for (auto &option: options) {
        if (!option.getLongOpt().empty()) {
            fprintf(getSourceFile(), "{\"%s\", ", option.getLongOpt().c_str());
            switch (option.isHasArguments()) {
                case HasArguments::OPTIONAL:
                    fprintf(getSourceFile(), "optional_argument, ");
                    break;
                case HasArguments::REQUIRED:
                    fprintf(getSourceFile(), "required_argument, ");
                    break;
                default:
                    fprintf(getSourceFile(), "no_argument, ");
                    break;
            }
            if (option.getShortOpt() == '\0')
                fprintf(getSourceFile(), "0, %i},\n", longOptsWithoutShortOpt++);
            else
                fprintf(getSourceFile(), "0, '%c'},\n", option.getShortOpt());
        }
    };
    longOptsWithoutShortOpt = 0;

    fprintf(getSourceFile(), "{0, 0, 0, 0}\n};\nint option_index = 0;\n\n");

    string shortOpts;
    for (auto &option: options) {
        if (option.getShortOpt() != '_') {
            shortOpts.append(1, option.getShortOpt());
            switch (option.isHasArguments()) {
                case HasArguments::OPTIONAL:
                    shortOpts.append("::");
                    break;
                case HasArguments::REQUIRED:
                    shortOpts.append(":");
                    break;
                default:
                    break;
            }
        }
    }

    fprintf(getSourceFile(), "while ((opt = getopt_long (argc, argv, \"%s\", long_options,"
                             " &option_index)) != -1){\n", shortOpts.c_str());

    //Variables for convertTo
    fprintf(getSourceFile(), "int convertedArgInt = 0;\nbool convertedArgBool = false;\n");

    //Hier switch case open
    fprintf(getSourceFile(), "switch (opt) {\n");
    for (auto &option: options) {
        string bothOpts;
        if(option.getShortOpt() != '\0') {
            bothOpts.append(1, option.getShortOpt());
            if(!option.getLongOpt().empty())
                bothOpts.append("/");
        }
        if(!option.getLongOpt().empty())
            bothOpts.append(option.getLongOpt());

        if (option.getShortOpt() != '\0')
            fprintf(getSourceFile(), "case '%c':\n", option.getShortOpt());
        else
            fprintf(getSourceFile(), "case %i:\n", longOptsWithoutShortOpt++);

        switch (option.isHasArguments()) {
            case HasArguments::REQUIRED:
                fprintf(getSourceFile(), "if(optarg == nullptr){\n"
                                         "perror(\"There was no argument passed for the option \\\"%s\\\" "
                                         "which requires one.\");\n"
                                         "exit(1);\n}", bothOpts.c_str());
                switch (option.getConvertTo()) {
                    case ConvertToOptions::INTEGER:
                        fprintf(getSourceFile(), "convertedArgInt = convertToInteger(optarg);\n");
                        break;
                    case ConvertToOptions::BOOLEAN:
                        fprintf(getSourceFile(), "convertedArgBool = convertToBoolean(optarg);\n");
                        break;
                    default:
                        break;
                }
                break;
            case HasArguments::OPTIONAL:
                switch (option.getConvertTo()) {
                    case ConvertToOptions::INTEGER:
                        fprintf(getSourceFile(), "if(optarg != nullptr)\n"
                                                 "convertedArgInt = convertToInteger(optarg);\n");
                        break;
                    case ConvertToOptions::BOOLEAN:
                        fprintf(getSourceFile(), "if(optarg != nullptr)\n"
                                                 "convertedArgBool = convertToBool(optarg);\n");
                        break;
                    default:
                        break;
                }
                break;
            default:
                fprintf(getSourceFile(), "if(optarg != nullptr){\n"
                                         "perror(\"There was an argument passed for the option \\\"%s\\\" "
                                         "which does not accept one.\");\nexit(1);}\n", bothOpts.c_str());
                break;
        }



        if (!option.getConnectToInternalMethod().empty())
            fprintf(getSourceFile(), "%s();\n", option.getConnectToInternalMethod().c_str());

        if (!option.getConnectToExternalMethod().empty()) {
            fprintf(getSourceFile(), "%s(", option.getConnectToExternalMethod().c_str());
            if (option.isHasArguments() == HasArguments::REQUIRED || option.isHasArguments() == HasArguments::OPTIONAL)
                switch (option.getConvertTo()) {
                case ConvertToOptions::INTEGER:
                    fprintf(getSourceFile(), "convertedArgInt");
                    break;
                case ConvertToOptions::BOOLEAN:
                    fprintf(getSourceFile(), "convertedArgBool");
                    break;
                default:
                    fprintf(getSourceFile(), "optarg");
                    break;
                }
            fprintf(getSourceFile(), ");\n");
        }

        //if(!option.getInterface().empty()){
          //fprintf(getSourceFile(), "setIsSet%s(true);");

        //}

        //Close case
        fprintf(getSourceFile(), "break;\n");
    };

    //Close switch-case
    fprintf(getSourceFile(), "case '?':\ndefault:\nif(isprint(optopt))\nunknownOption(optopt);\n"
                             "else\nunknownOption(std::to_string(optopt));\nbreak;}\n");
    //Close while loop
    fprintf(getSourceFile(), "}\n");
    //Close function parseOptions
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
