#include "COptionParser.h"
#include <cstring>
#include <boost/lexical_cast.hpp>

namespace DHBW {
    // Getter
    std::string COptionParser::getValueOfOutputPath() const {
        return outputPathValue;
    }

    bool COptionParser::isSetOutputPath() const {
        return args.outputPath.isSet;
    }

    void COptionParser::parse() {
        // Check if getopt was set and execute functions if no exclusion
        if (args.help.isSet) {
            if (args.version.isSet) {
                perror ("--help and --version cannot be used together.");
                exit(1);
            }

            // More exclusions here in other if statements
        }

        if (args.version.isSet) {
            if (args.help.isSet) {
                perror ("--version and --help cannot be used together.");
                exit(1);
            }

            // More exclusions here in other if statements
        }

        if (args.outputPath.isSet) {
            // More exclusions here in other if statements
        }

        // Run code here
        if (args.help.isSet) {
            printHelp();
        }

        if (args.version.isSet) {
            printVersion();
        }

        if (args.outputPath.isSet) {
            // Set values of argument optional or required and param not empty
            outputPathValue = boost::lexical_cast<typeof outputPathValue>(args.outputPath.value);
            // Interface doesn't need function call
        }
    }

    void COptionParser::printHelp() {
        printf("Executed printHelp()\n");
    }

    void COptionParser::printVersion() {
        printf("Executed printVersion()\n");
    }

    void COptionParser::parseOptions(int argc, char **argv) {
        args = Args();

        int digit_optind = 0;

        while (true) {
            int c;

            int this_option_optind = optind ? optind : 1;
            int option_index = 0;
            static struct option long_options[] = {
                    {"help",     no_argument, 0,  0 },
                    {"version",  no_argument, 0,  0 },
                    {"out-path",  required_argument, 0, 0 },
                    {0, 0, 0, 0}
            };

            c = getopt_long(argc, argv, "hv", long_options, &option_index);
            if (c == -1) {
                break;
            }

            switch (c) {
                case 0:
                    // LongOpts
                    if (strcmp("help", long_options[option_index].name) == 0) {
                        args.help.isSet = true;
                    }
                    if (strcmp("version", long_options[option_index].name) == 0) {
                        args.version.isSet = true;
                    }
                    if (strcmp("out-path", long_options[option_index].name) == 0) {
                        args.outputPath.isSet = true;
                        // Only add value if Arguments is Required or Optional
                        args.outputPath.value = optarg;
                    }
                    break;

                    // ShortOpts
                case 'h':
                    args.help.isSet = true;
                    break;

                case 'v':
                    args.version.isSet = true;
                    break;

                default:
                    printf("?? getopt returned character code 0%o ??\n", c);
            }
        }

        if (optind < argc) {
            printf("non-option ARGV-elements: ");
            while (optind < argc)
                printf("%s ", argv[optind++]);
            printf("\n");
        }

        // Parse the arguments
        parse();

        exit(EXIT_SUCCESS);
    }
}

int main(int argc, char* argv[]) {
    DHBW::COptionParser parser;
    parser.parseOptions(argc, argv);
}