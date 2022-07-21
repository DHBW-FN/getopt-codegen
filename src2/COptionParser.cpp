//https://gist.github.com/avances123/2406651
#include "COptionParser.h"
#include <cstring>
#include <string>

namespace DHBW {
    void COptionParser::parse(Args args) {
        // Check if getopt was set and execute functions if no exclusion

        bool state[2];
        state[0] = args.help;
        state[1] = args.version;

        if (state[0] && !state[1]) {
            printHelp();
            return;
        }

        if (!state[0] && state[1]) {
            printVersion();
            return;
        }

        std::string error = "The combination of: ";
        if (state[0]) {
            error += "-h ";
        }

        if (state[1]) {
            error += "-v ";
        }
        error += "is not allowed.\n";
        printf("%s", error.c_str());
    }

    void COptionParser::printHelp() {
        printf("hallo");
    }

    void COptionParser::printVersion() {
    }

    //immer wenn connectToInternalMethod() aufgerufen wird, muss diese Funktion aufgerufen werden
    //natürlich mit dem entsprechenden Methodennamen
    void COptionParser::ParseXml() {
    }
}

int main(int argc, char* argv[]) {
    using namespace DHBW;

    int digit_optind = 0;

    Args args;

    while (true) {
        int c;

        int this_option_optind = optind ? optind : 1;
        int option_index = 0;
        static struct option long_options[] = {
                {"help",     no_argument, 0,  0 },
                {0,         0,                 0,  0 }
        };

        c = getopt_long(argc, argv, "hv", long_options, &option_index);
        if (c == -1) {
            break;
        }

        switch (c) {
            case 0:
                // LongOpts
                if (strcmp("help", long_options[option_index].name) == 0) {
                    args.help = true;
                }
                if (strcmp("version", long_options[option_index].name) == 0) {
                    args.version = true;
                }

                // Check if called with arguments
                if (optarg)
                    printf(" with arg %s", optarg);
                printf("\n");
                break;

            // ShortOpts
            case 'h':
                args.help = true;
                break;

            case 'v':
                args.version = true;
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

    // Initialize parser and parse arguments
    COptionParser parser;
    parser.parse(args);

    exit(EXIT_SUCCESS);
}