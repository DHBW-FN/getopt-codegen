/*
 * Editors: Philipp Kuest, Tobias Goetz
 */

#ifndef CODEGENERATOR_EXAMPLEPROGRAM_H
#define CODEGENERATOR_EXAMPLEPROGRAM_H


#include "ExtendedGeneratedCode.h"

class ExampleProgram {
private:
    GC::GeneratedClass *generatedClass = nullptr;
protected:
public:
    /**
    * @brief Constructor, that generates a object of ExtendedGeneratedCode
    */
    explicit ExampleProgram(GC::GeneratedClass *generatedClass);

    /**
    * @brief Getter for generatedClass
    * @return object of class ExtendedGeneratedCode
    */
    GC::GeneratedClass *getGeneratedClass();
};


#endif //CODEGENERATOR_EXAMPLEPROGRAM_H
