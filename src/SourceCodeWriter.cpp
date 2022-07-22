#include "SourceCodeWriter.h"
#include <boost/algorithm/string.hpp>

// Constructor
SourceCodeWriter::SourceCodeWriter(GetOptSetup *getOptSetup) {
    if (getOptSetup->getSourceFileName().empty() || getOptSetup->getHeaderFileName().empty()) {
        perror("Both the Header-Filename and the Sourcefilename must be set.");
        exit(1);
    }

    if (getOptSetup->getClassName().empty()) {
        perror("The Class-Name must be set. ");
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

    // Close header file
    fprintf(getHeaderFile(), "\n#endif //%s_H", defineString.c_str());
}

void SourceCodeWriter::headerFileNamespace() {
    //start of namespace
    if (!getGetOptSetup()->getNamespaceName().empty()) {
        fprintf(getHeaderFile(), "namespace %s {\n\n", getGetOptSetup()->getNamespaceName().c_str());
    }

    //put all elements inside namespace here
    createHeaderStructArgs();
    headerFileClass();

    //end of namespace
    if (!getGetOptSetup()->getNamespaceName().empty()) {
        fprintf(getHeaderFile(), "}\n");
    }
}

void SourceCodeWriter::headerFileClass() {
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
    createHeaderGetter();
    createHeaderParsingFunction();
    createHeaderUnknownOption();

    //end of class
    fprintf(getHeaderFile(), "};\n");
}

void SourceCodeWriter::createHeaderStructArgs() {
    fprintf(getHeaderFile(), "struct Args {\n");
    for (auto &option: getGetOptSetup()->getOptions()) {
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

void SourceCodeWriter::sourceFileNamespace() {
    //start of namespace
    if (!getGetOptSetup()->getNamespaceName().empty()) {
        fprintf(getSourceFile(), "namespace %s {\n\n", getGetOptSetup()->getNamespaceName().c_str());
    }
    createSourceGetter();

    createSourceParsingFunction();
    createSourceUnknownOption();

    //Hier kommt der Help-Text dazu

    //put all elements inside namespace here

    //end of namespace
    if (!getGetOptSetup()->getNamespaceName().empty()) {
        fprintf(getSourceFile(), "}\n");
    }
}

void SourceCodeWriter::createHeaderParsingFunction() {
    fprintf(getHeaderFile(), "void parseOptions(int argc, char **argv);\n");
}

void SourceCodeWriter::createSourceParsingFunction() {
    vector<Option> options = getGetOptSetup()->getOptions();
    fprintf(getSourceFile(), "void %s::parseOptions(int argc, char **argv){\nargs = Args();\n"
                             "opterr = 0;\nint opt;\nstatic struct option long_options[] = {\n",
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

    //Hier switch case open
    fprintf(getSourceFile(), "switch (opt) {\n");
    for (auto &option: options) {
        string bothOpts;
        if (option.getShortOpt() != '\0') {
            bothOpts.append(1, option.getShortOpt());
            if (!option.getLongOpt().empty())
                bothOpts.append("/");
        }
        if (!option.getLongOpt().empty())
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
                                         "exit(1);\n}\nargs.%s.value = optarg;\n",
                        bothOpts.c_str(), determineArgsName(option).c_str());
                break;
            case HasArguments::OPTIONAL:
                fprintf(getSourceFile(), "if(optarg != nullptr)\nargs.%s.value = optarg;",
                        determineArgsName(option).c_str());
                break;
            default:
                fprintf(getSourceFile(), "if(optarg != nullptr){\n"
                                         "perror(\"There was an argument passed for the option \\\"%s\\\" "
                                         "which does not accept one.\");\nexit(1);}\n", bothOpts.c_str());
                break;
        }

        fprintf(getSourceFile(), "args.%s.isSet = true;", determineArgsName(option).c_str());

        //Close case
        fprintf(getSourceFile(), "break;\n");
    };

    //Close switch-case
    fprintf(getSourceFile(), "case '?':\ndefault:\nunknownOption(std::to_string(optopt));\nbreak;}\n");
    //Close while loop
    fprintf(getSourceFile(), "}\n");

    //Print argv-Arguments that were too much
    fprintf(getSourceFile(), "if (optind < argc){\nprintf(\"non-option ARGV-elements: \");\n"
                             "while (optind < argc)\nprintf(\"%s \", argv[optind++]);\nprintf(\"\\n\");\n}\n", "%s");

    //Call parse-function
    fprintf(getSourceFile(), "parse(args);\n\n");

    //If nothing went wrong -> EXIT_SUCCESS
    fprintf(getSourceFile(), "exit(EXIT_SUCCESS);\n");

    //Close function parseOptions
    fprintf(getSourceFile(), "}\n");
}

void SourceCodeWriter::createHeaderUnknownOption() {
    fprintf(getHeaderFile(), "virtual void unknownOption(const std::string &unknownOption);\n\n");
}

void SourceCodeWriter::createSourceUnknownOption() {
    fprintf(getSourceFile(), "void %s::unknownOption(const std::string &unknownOption){\n"
                             "perror(\"GetOpt encountered an unknown option.\");\n"
                             "exit(1);\n}\n", getGetOptSetup()->getClassName().c_str());
}

// Helper functions
std::string SourceCodeWriter::determineArgsName(const Option &option) {
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

void SourceCodeWriter::createHeaderGetter() {
    vector<Option> options = getGetOptSetup()->getOptions();
    for (auto &option: options) {
        string capitalizedArgsName = determineArgsName(option);
        capitalizedArgsName[0] = toupper(capitalizedArgsName[0]);
        if (!option.getInterface().empty()) {
            fprintf(getHeaderFile(), "bool isSet%s() const;\n", capitalizedArgsName.c_str());
            if (option.isHasArguments() != HasArguments::None) {
                std::string type;
                switch (option.getConvertTo()) {
                    case ConvertToOptions::INTEGER:
                        type = "int";
                        break;
                    case ConvertToOptions::BOOLEAN:
                        type = "bool";
                        break;
                    case ConvertToOptions::STRING:
                        type = "std::string";
                        break;
                }
                fprintf(getHeaderFile(), "%s getValueOf%s() const;\n",
                        type.c_str(), capitalizedArgsName.c_str());
            }
        } else if (option.getInterface().empty() && option.getConnectToInternalMethod().empty()
                   && option.getConnectToExternalMethod().empty()) {
            fprintf(getHeaderFile(), "bool isSet%s() const;\n", capitalizedArgsName.c_str());
        }
    }
}

void SourceCodeWriter::createSourceGetter() {
    vector<Option> options = getGetOptSetup()->getOptions();
    for (auto &option: options) {
        string capitalizedArgsName = determineArgsName(option);
        capitalizedArgsName[0] = toupper(capitalizedArgsName[0]);
        if (!option.getInterface().empty()) {
            fprintf(getSourceFile(), "bool %s::isSet%s() const {\nreturn args.%s.isSet;\n}\n",
                    getGetOptSetup()->getClassName().c_str(), capitalizedArgsName.c_str(),
                    determineArgsName(option).c_str());
            if (option.isHasArguments() != HasArguments::None) {
                std::string type;
                switch (option.getConvertTo()) {
                    case ConvertToOptions::INTEGER:
                        type = "int";
                        break;
                    case ConvertToOptions::BOOLEAN:
                        type = "bool";
                        break;
                    case ConvertToOptions::STRING:
                        type = "std::string";
                        break;
                }
                fprintf(getSourceFile(), "%s %s::getValueOf%s() const{\nreturn %sValue;\n}\n",
                        type.c_str(), getGetOptSetup()->getClassName().c_str(), capitalizedArgsName.c_str(),
                        determineArgsName(option).c_str());
            }
        } else if (option.getInterface().empty() && option.getConnectToInternalMethod().empty()
                   && option.getConnectToExternalMethod().empty()) {
            fprintf(getSourceFile(), "bool %s::isSet%s() const {\nreturn args.%s.isSet;\n}\n",
                    getGetOptSetup()->getClassName().c_str(), capitalizedArgsName.c_str(),
                    determineArgsName(option).c_str());
        }
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
