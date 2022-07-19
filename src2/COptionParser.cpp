//https://gist.github.com/avances123/2406651
#include "COptionParser.h"
#include <string.h>

namespace DHBW {
    void printHelp() {
        printf("printHelp() called\n");
    }

    void printVersion() {
        printf("printVersion() called\n");
    }
}
int main(int argc, char* argv[]) {
    using namespace DHBW;

    int c;
    int digit_optind = 0;

    while (true) {
        int this_option_optind = optind ? optind : 1;
        int option_index = 0;
        static struct option long_options[] = {
                {"help",     no_argument, 0,  0 },
                {0,         0,                 0,  0 }
        };

        c = getopt_long(argc, argv, "hv",
                        long_options, &option_index);
        if (c == -1) {
            break;
        }

        switch (c) {
            case 0:
                if (strcmp("help", long_options[option_index].name) == 0) {
                    printHelp();
                } else if (strcmp("version", long_options[option_index].name) == 0) {
                    printVersion();
                }

                // Check if called with arguments
                if (optarg)
                    printf(" with arg %s", optarg);
                printf("\n");
                break;

            case 'h':
                for (int i = 0; i <= argc; ++i) {
                    printf("%s\n", argv[i]);
                }
                printHelp();
                break;

            case 'v':
                printVersion();
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

    exit(EXIT_SUCCESS);
}