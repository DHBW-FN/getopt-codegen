#ifndef CODEGENERATOR_EXTENDEDGENERATEDCODE_H
#define CODEGENERATOR_EXTENDEDGENERATEDCODE_H

#include "generatedCode.h"

/**
 * class with inheritance to generated class to use getopt of generated files
 */
class ExtendedGeneratedCode: public GC::GeneratedClass {

    /**
     * @brief overrides printVersion function in generated Code
     */
    void printVersion() override;
};


#endif //CODEGENERATOR_EXTENDEDGENERATEDCODE_H
