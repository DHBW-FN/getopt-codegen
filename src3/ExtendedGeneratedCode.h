#ifndef CODEGENERATOR_EXTENDEDGENERATEDCODE_H
#define CODEGENERATOR_EXTENDEDGENERATEDCODE_H

#include "generatedCode.h"

/**
 * class with inheritance to generated class to use getopt of generated files
 */
class ExtendedGeneratedCode: public GC::GeneratedClass {
    void printVersion() override {
        printf("Version: 2.0.0\n");
    };
};


#endif //CODEGENERATOR_EXTENDEDGENERATEDCODE_H
