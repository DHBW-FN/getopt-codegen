#ifndef CODEGENERATOR_COPTIONPARSER_H
#define CODEGENERATOR_COPTIONPARSER_H

#include <getopt.h>
#include <cstdio>     /* for printf */
#include <cstdlib>    /* for exit */

struct Args {
    bool help = false;
    bool version = false;
};

namespace DHBW {

    class COptionParser {
    private:
    protected:
        virtual void printHelp();
        virtual void printVersion();
    public:
        void parse(Args args);
    };
}

#endif //CODEGENERATOR_COPTIONPARSER_H
