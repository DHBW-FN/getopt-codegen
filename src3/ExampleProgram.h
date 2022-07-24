#ifndef CODEGENERATOR_EXAMPLEPROGRAM_H
#define CODEGENERATOR_EXAMPLEPROGRAM_H


#include "ExtendedGeneratedCode.h"

class ExampleProgram {
private:
    GC::GeneratedClass *generatedClass = nullptr;
protected:
public:
    //Constructor
    explicit ExampleProgram(GC::GeneratedClass *generatedClass);

    //Getter
    GC::GeneratedClass *getGeneratedClass();
};


#endif //CODEGENERATOR_EXAMPLEPROGRAM_H
