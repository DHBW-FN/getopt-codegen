/*
 * Editors: Tobias Goetz, Noel Kempter, Philipp Kuest, Sebastian Wolf
 */

#ifndef CODEGENERATOR_COPTIONPARSER_H
#define CODEGENERATOR_COPTIONPARSER_H

#include <getopt.h>
#include <string>
#include <cstdio>     /* for printf */
#include <cstdlib>    /* for exit */

struct Args {
    struct {
        bool isSet = false;
    } help;

    struct {
        bool isSet = false;
    } version;

    // Important: Name priority Interface > LongOpt > ShortOpt and remove the "-" from the name
    struct {
        bool isSet = false;
        // Only add value if Arguments is Required or Optional
        std::string value;
    } outputPath;
};

namespace DHBW {

    class COptionParser {
    private:
        Args args;

        std::string outputPathValue;
    protected:
        virtual void printHelp();
        virtual void printVersion();
    public:
        void parse();

        // Getter
        std::string getValueOfOutputPath() const;
        bool isSetOutputPath() const;

        // Helper
        void parseOptions(int argc, char* argv[]);
    };
}

#endif //CODEGENERATOR_COPTIONPARSER_H
