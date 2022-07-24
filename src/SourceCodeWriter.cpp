/*
 * Editors: Tobias Goetz, Noel Kempter, Philipp Kuest, Sebastian Wolf, Niklas Holl
 */

#include "SourceCodeWriter.h"
#include "Logger.h"
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
        setHeaderFile(fopen(getGetOptSetup()->getHeaderFileName().c_str(), "w"));
    }
    return headerFile;
}

FILE *SourceCodeWriter::getSourceFile() {
    if (sourceFile == nullptr) {
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
 * @brief get string of the type of the option
 * @param option a single option object
 * @return string with correct value type
 */
string SourceCodeWriter::getValueTypeByOption(Option &option)
{
    switch (option.getConvertTo()) {
        case ConvertToOptions::STRING:
            return "std::string";
        case ConvertToOptions::INTEGER:
            return "int";
        case ConvertToOptions::BOOLEAN:
            return "bool";
        default:
            return "";
    }
}

//from here on are all the headerFiles
void SourceCodeWriter::headerFileIncludes() {
    // Define static and always used includes here
    string includes[] = {"getopt.h", "iostream", "boost/lexical_cast.hpp"};

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

    // Values for the options
    for (Option option: getGetOptSetup()->getOptions()) {
        if (option.isHasArguments() != HasArguments::NONE) {
            fprintf(getHeaderFile(), "%s %sValue", getValueTypeByOption(option).c_str(), determineArgsName(option).c_str());
            if (option.isHasArguments() == HasArguments::OPTIONAL && !option.getDefaultValue().empty()) {
                switch (option.getConvertTo()) {
                    case ConvertToOptions::STRING:
                        fprintf(getHeaderFile(), " = \"%s\"", option.getDefaultValue().c_str());
                        break;
                    case ConvertToOptions::INTEGER:
                    case ConvertToOptions::BOOLEAN:
                        fprintf(getHeaderFile(), " = %s", option.getDefaultValue().c_str());
                        break;
                    default:
                        break;
                }
            }
            fprintf(getHeaderFile(), ";\n");
        }
    }

    createHeaderPrintVersion();
    fprintf(getHeaderFile(), "\n");
    fprintf(getHeaderFile(), "protected:\n");
    //put all elements inside class -> protected here

    fprintf(getHeaderFile(), "\n");
    fprintf(getHeaderFile(), "public:\n");
    //put all elements inside class -> public here
    fprintf(getHeaderFile(), "void parse();\n");
    createHeaderGetter();
    createExternalFunctions();
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
        if (option.isHasArguments() != HasArguments::NONE) {
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
    createSourcePrintVersion();
    //put all elements inside namespace here
    sourceFileParse();
    createSourceParsingFunction();
    createSourceUnknownOption();

    //Hier kommt der Help-Text dazu

    //end of namespace
    if (!getGetOptSetup()->getNamespaceName().empty()) {
        fprintf(getSourceFile(), "}\n");
    }
}

void SourceCodeWriter::createHeaderParsingFunction() {
    fprintf(getHeaderFile(), "void parseOptions(int argc, char **argv);\n");
}

void SourceCodeWriter::sourceFileParse() {
    fprintf(getSourceFile(), "void %s::parse() {\n", getGetOptSetup()->getClassName().c_str());
    for (auto &option : getGetOptSetup()->getOptions()) {
        std::string optionName = determineArgsName(option);
        fprintf(getSourceFile(), "if (args.%s.isSet) {\n", optionName.c_str());

        // exclusions
        if (!option.getExclusions().empty()) {
            for (auto &exclusion : option.getExclusions()) {
                // Iterate over options again and compare exclusion with ref
                for (auto &option2 : getGetOptSetup()->getOptions()) {
                    std::string option2Name = determineArgsName(option2);
                    if (option2.getRef() == exclusion) {
                        fprintf(getSourceFile(), "if (args.%s.isSet) {\n", option2Name.c_str());
                        fprintf(getSourceFile(), "perror(\"%s and %s cannot be used together.\");\n", optionName.c_str(), option2Name.c_str());
                        fprintf(getSourceFile(), "exit(1);\n");
                        fprintf(getSourceFile(), "}\n");
                    }
                }
            }
        }
        fprintf(getSourceFile(), "}\n");
    }

    for (Option option: getGetOptSetup()->getOptions()) {
        std::string optionName = determineArgsName(option);
        fprintf(getSourceFile(), "if (args.%s.isSet) {\n", optionName.c_str());

        //Handle option
        if (option.isHasArguments() != HasArguments::NONE) {
            fprintf(getSourceFile(), "if (!args.%s.value.empty()) {\n", optionName.c_str());
            //TODO This might not work this way, check back later
            fprintf(getSourceFile(), "try {\n");
            fprintf(getSourceFile(), "%sValue = boost::lexical_cast<typeof %sValue>(args.%s.value);\n", optionName.c_str(), optionName.c_str(), optionName.c_str());
            fprintf(getSourceFile(), "} catch (boost::bad_lexical_cast &) {\n");
            fprintf(getSourceFile(), "perror(\"%s is not convertible to %s.\");\n}\n", optionName.c_str(), getValueTypeByOption(option).c_str());
            fprintf(getSourceFile(), "}\n");
        }

        if (!option.getConnectToInternalMethod().empty()) {
            fprintf(getSourceFile(), "%s(", option.getConnectToInternalMethod().c_str());
            if (option.isHasArguments() != HasArguments::NONE) {
                fprintf(getSourceFile(), "%sValue", optionName.c_str());
            }
            fprintf(getSourceFile(), ");\n");
        }

        if (!option.getConnectToExternalMethod().empty()) {
            fprintf(getSourceFile(), "%s(", option.getConnectToExternalMethod().c_str());
            if (option.isHasArguments() != HasArguments::NONE) {
                fprintf(getSourceFile(), "%sValue", optionName.c_str());
            }
            fprintf(getSourceFile(), ");\n");
        }
        fprintf(getSourceFile(), "}\n");
    }
    fprintf(getSourceFile(), "}\n");
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
        if (option.getShortOpt() != '\0') {
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
                if (option.getConvertTo() == ConvertToOptions::BOOLEAN) {
                    fprintf(getSourceFile(), "if(strcmp(optarg, \"true\"))\nargs.%s.value = \"1\";\n"
                                             "else if(strcmp(optarg, \"false\"))\nargs.%s.value = \"0\";\n"
                                             "else\nargs.%s.value = optarg;\n",
                            determineArgsName(option).c_str(), determineArgsName(option).c_str(),
                            determineArgsName(option).c_str());
                } else
                    fprintf(getSourceFile(), "args.%s.value = optarg;\n",
                            determineArgsName(option).c_str());
                break;
            case HasArguments::OPTIONAL:
                fprintf(getSourceFile(), "if(optarg != nullptr)\nargs.%s.value = optarg;",
                        determineArgsName(option).c_str());
                if (option.getConvertTo() == ConvertToOptions::BOOLEAN) {
                    fprintf(getSourceFile(), "if(strcmp(optarg, \"true\"))\nargs.%s.value = \"1\";\n"
                                             "else if(strcmp(optarg, \"false\"))\nargs.%s.value = \"0\";\n"
                                             "else\nargs.%s.value = optarg;\n",
                            determineArgsName(option).c_str(), determineArgsName(option).c_str(),
                            determineArgsName(option).c_str());
                } else
                    fprintf(getSourceFile(), "args.%s.value = optarg;\n",
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
    fprintf(getSourceFile(), "parse();\n");

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
    for (Option option: getGetOptSetup()->getOptions()) {
        string capitalizedArgsName = determineArgsName(option);
        capitalizedArgsName[0] = toupper(capitalizedArgsName[0], locale());
        if (!option.getInterface().empty()) {
            fprintf(getHeaderFile(), "bool isSet%s() const;\n", capitalizedArgsName.c_str());
            if (option.isHasArguments() != HasArguments::NONE) {
                fprintf(getHeaderFile(), "%s getValueOf%s() const;\n",
                        getValueTypeByOption(option).c_str(), capitalizedArgsName.c_str());
            }
        } else if (option.getInterface().empty() && option.getConnectToInternalMethod().empty()
                   && option.getConnectToExternalMethod().empty()) {
            fprintf(getHeaderFile(), "bool isSet%s() const;\n", capitalizedArgsName.c_str());
        }
    }
}

void SourceCodeWriter::createSourceGetter() {
    for (Option option: getGetOptSetup()->getOptions()) {
        string capitalizedArgsName = determineArgsName(option);
        capitalizedArgsName[0] = toupper(capitalizedArgsName[0], locale());
        if (!option.getInterface().empty()) {
            fprintf(getSourceFile(), "bool %s::isSet%s() const {\nreturn args.%s.isSet;\n}\n",
                    getGetOptSetup()->getClassName().c_str(), capitalizedArgsName.c_str(),
                    determineArgsName(option).c_str());
            if (option.isHasArguments() != HasArguments::NONE) {
                fprintf(getSourceFile(), "%s %s::getValueOf%s() const{\nreturn %sValue;\n}\n",
                        getValueTypeByOption(option).c_str(), getGetOptSetup()->getClassName().c_str(), capitalizedArgsName.c_str(),
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

void SourceCodeWriter::createExternalFunctions() {
    vector<Option> options = getGetOptSetup()->getOptions();

    for(auto &option : options){
        if(!option.getConnectToExternalMethod().empty()){
            fprintf(getHeaderFile(), "virtual void %s(", option.getConnectToExternalMethod().c_str());
            if(option.isHasArguments() == HasArguments::OPTIONAL || option.isHasArguments() == HasArguments::REQUIRED){
                std::string type = getValueTypeByOption(option);
                fprintf(getHeaderFile(), "%s arg", type.c_str());
            }
            fprintf(getHeaderFile(), ") = 0;\n");
        }
    }
}

void SourceCodeWriter::createHeaderPrintVersion() {
    fprintf(getHeaderFile(), "virtual void printVersion();\n");

}

void SourceCodeWriter::createSourcePrintVersion() {
    fprintf(getSourceFile(), "void %s::printVersion(){\nprintf(\"version: 1.0.0\");\n}\n",
            getGetOptSetup()->getClassName().c_str());

}

void SourceCodeWriter::writeFile() {
    LOG_INFO("Starting to write source code...");
//    printf("Writing file...\n");

    //Write header files --> put methods here
    headerFileIncludes();

    //Write source files --> put methods here
    sourceFileIncludes();
    sourceFileNamespace();
    LOG_INFO("Finished writing source code.");
}

