//https://gist.github.com/avances123/2406651

//Start: include + define
#include "COptionParser.h"
#include <cstring>
//End: include + define

//Start: namespace
namespace DHBW {
//End: namespace

//Start: COptionParser
    void COptionParser::parse(Args args) {
//End: COptionParser
        // Check if getopt was set and execute functions if no exclusion
        //TO DO: print wrong combination of options

//Start: one block of --> exclusion
        if (args.help && !(args.version)) {
            printHelp();
            return;
        }
//End: one block of --> exclusion

//Start: one block of --> exclusion
        if (args.version && !(args.help)) {
            printVersion();
            return;
        }
//End: one block of --> exclusion

//Start: endOfExclusion (muss eh noch verändert werden, um die entsprechenden exclusions auszugeben)
        perror("Darfst du nicht!\n");
        exit(1);
//End: endOfExclusion

//EndOfCOptionParser
    }

//wenn ich es richtig verstanden habe wird das immer bei connectToInternalMethod eingefügt
//Start: one block of --> connectToInternalMethod
    void COptionParser::printHelp() {
        printf("hallo");
    }
//End: connectToInternalMethod

//Start: one block of --> connectToInternalMethod
    void COptionParser::printVersion() {
    }
//End: connectToInternalMethod

    //immer wenn connectToInternalMethod() aufgerufen wird, muss diese Funktion aufgerufen werden
    //natürlich mit dem entsprechenden Methodennamen
    void COptionParser::ParseXml() {
    }

//End of namespace
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